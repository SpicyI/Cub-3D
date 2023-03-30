/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2d_rendring.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 22:59:47 by del-khay          #+#    #+#             */
/*   Updated: 2023/03/30 04:59:30 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

void	draw_ray(t_mlx *mlx, t_ray *ray)
{
	if (mlx->_m.display_map > 0)
	{
		if ((ray->x / ray->scale_factor) * mlx->_m.map_scale < mlx->_p.player_x
			+ 100 && (ray->y / ray->scale_factor)
			* mlx->_m.map_scale < mlx->_p.player_y + 100)
			my_mlx_pixel_put(mlx, (ray->x / ray->scale_factor)
				* mlx->_m.map_scale, (ray->y / ray->scale_factor)
				* mlx->_m.map_scale, RAYCOLOR);
	}
	else
		my_mlx_pixel_put(mlx, (ray->x / ray->scale_factor) * mlx->_m.map_scale,
			(ray->y / ray->scale_factor) * mlx->_m.map_scale, RAYCOLOR);
}

float	calculate_distance(t_mlx *mlx, t_ray *ray)
{
	float	distance_to_wall;

	ray->hit_point[X] = (ray->x / ray->scale_factor) * mlx->_m.map_scale;
	ray->hit_point[Y] = (ray->y / ray->scale_factor) * mlx->_m.map_scale;
	distance_to_wall = sqrt(pow(ray->x - ((mlx->_p.player_x / mlx->_m.map_scale)
					* ray->scale_factor), 2) + pow(ray->y - ((mlx->_p.player_y
						/ mlx->_m.map_scale) * ray->scale_factor), 2));
	distance_to_wall *= cos(mlx->_p.player_angle - ray->ray_angle);
	return (distance_to_wall);
}

int	hit_wall(t_mlx *mlx, t_ray *ray, int i)
{
	ray->x = floor((cos(ray->ray_angle) * i) + (((mlx->_p.player_x
						/ mlx->_m.map_scale) * ray->scale_factor)));
	if (mlx->_m.map[(int)ray->y / SCALEFACTOR][(int)ray->x
		/ SCALEFACTOR] == '1')
	{
		ray->hit_side = VERTICAL;
		return (1);
	}
	ray->y = floor((sin(ray->ray_angle) * i) + ((mlx->_p.player_y
					/ mlx->_m.map_scale) * ray->scale_factor));
	if (mlx->_m.map[(int)ray->y / SCALEFACTOR][(int)ray->x
		/ SCALEFACTOR] == '1')
	{
		ray->hit_side = HORIZONTAL;
		return (1);
	}
	return (0);
}

float	cast(t_ray *ray, t_mlx *mlx)
{
	int		i;
	float	distance_to_wall;

	i = 0;
	ray->x = (cos(ray->ray_angle) * i) + ((mlx->_p.player_x / mlx->_m.map_scale)
			* ray->scale_factor);
	ray->y = (sin(ray->ray_angle) * i) + ((mlx->_p.player_y / mlx->_m.map_scale)
			* ray->scale_factor);
	while (1)
	{
		draw_ray(mlx, ray);
		if (hit_wall(mlx, ray, i))
			break ;
		i++;
	}
	distance_to_wall = calculate_distance(mlx, ray);
	return (distance_to_wall);
}

void	init_ray(t_ray *ray, t_mlx *mlx)
{
	ray->ray_angle = mlx->_p.player_angle - (mlx->fov / 2);
	ray->max_angle = mlx->_p.player_angle + (mlx->fov / 2);
	ray->rays_number = RAYNUMBER;
	ray->scale_factor = SCALEFACTOR;
	ray->step = mlx->fov / ray->rays_number;
}

int	get_color(t_ray *ray, t_mlx *mlx)
{
	int	color;

	color = 0;
	if (ray->hit_point[Y] - mlx->_p.player_y < 0 && ray->hit_side == HORIZONTAL)
		color = 0x00555652;
	if (ray->hit_point[Y] - mlx->_p.player_y >= 0
		&& ray->hit_side == HORIZONTAL)
		color = METAL;
	if (ray->hit_point[X] - mlx->_p.player_x < 0 && ray->hit_side == VERTICAL)
		color = shader(WHITE, 50);
	if (ray->hit_point[X] - mlx->_p.player_x >= 0 && ray->hit_side == VERTICAL)
		color = shader(0x00505652, 40);
	return (color);
}

void	ray_caster(t_mlx *mlx)
{
	t_ray	ray;
	int		i;

	init_ray(&ray, mlx);
	i = 0;
	while (i < ray.rays_number)
	{
		mlx->distances[i] = cast(&ray, mlx);
		mlx->ray_color[i] = get_color(&ray, mlx);
		ray.ray_angle += ray.step;
		i++;
	}
}
