/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2d_rendring.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 22:59:47 by del-khay          #+#    #+#             */
/*   Updated: 2023/03/31 04:19:27 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

// void	draw_ray(t_mlx *mlx, t_ray *ray)
// {
// 	if (mlx->_m.display_map > 0)
// 	{
// 		if ((ray->x / ray->scale_factor) * mlx->_m.map_scale < mlx->_p.player_x
// 			+ 100 && (ray->y / ray->scale_factor)
// 			* mlx->_m.map_scale < mlx->_p.player_y + 100)
// 			my_mlx_pixel_put(mlx, (ray->x / ray->scale_factor)
// 				* mlx->_m.map_scale, (ray->y / ray->scale_factor)
// 				* mlx->_m.map_scale, RAYCOLOR);
// 	}
// 	else
// 		my_mlx_pixel_put(mlx, (ray->x / ray->scale_factor) * mlx->_m.map_scale,
// 			(ray->y / ray->scale_factor) * mlx->_m.map_scale, RAYCOLOR);
// }

float get_distance(t_mlx *mlx, t_inter *r)
{
	float hit_distance;

	while (1)
	{
		if (r->x_inter < 0 || r->x_inter > mlx->_m.map_width * mlx->_m.map_scale
			|| r->y_inter < 0 || r->y_inter > mlx->_m.map_height * mlx->_m.map_scale)
			break ;
		if (mlx->_m.map[(int)(r->y_inter / mlx->_m.map_scale)][(int)(r->x_inter / mlx->_m.map_scale)] == '1')
			break ;
		r->x_inter += r->xstep;
		r->y_inter += r->ystep;
	}
	r->hit_x = r->x_inter;
	r->hit_y = r->y_inter;
	hit_distance = sqrt(pow(mlx->_p.player_x - r->x_inter, 2) + pow(mlx->_p.player_y - r->y_inter, 2));
	return (hit_distance);
}

float horizontal_hit(t_mlx *mlx , t_ray * ray, t_inter *r)
{	
	float   hit_distance;
	
	r->ystep = mlx->_m.map_scale;
	r->xstep = mlx->_m.map_scale / tan(ray->ray_angle);
	r->y_inter = floor(mlx->_p.player_y / mlx->_m.map_scale) * mlx->_m.map_scale;
	if (ray->ray_angle < M_PI && ray->ray_angle > 0)
		r->y_inter += mlx->_m.map_scale; 
	else 
		r->ystep *= -1;
	if (r->xstep < 0 && (ray->ray_angle < M_PI / 2 || ray->ray_angle > 1.5 * M_PI))
		r->xstep *= -1;
	if (r->xstep > 0 && !(ray->ray_angle < M_PI / 2 || ray->ray_angle > 1.5 * M_PI))
		r->xstep *= -1;
	r->x_inter = mlx->_p.player_x + ((r->y_inter - mlx->_p.player_y) / tan(ray->ray_angle));
	if (!(ray->ray_angle < M_PI && ray->ray_angle > 0))
		r->y_inter--;
	hit_distance = get_distance(mlx, r);
	return (hit_distance);
}

float vertical_hit(t_mlx *mlx , t_ray *ray , t_inter *r)
{
	float   hit_distance;
	
	ray->ray_angle = fmod(ray->ray_angle ,(2 * M_PI));
	if (ray->ray_angle < 0)
		ray->ray_angle += (2 * M_PI);
	r->xstep = mlx->_m.map_scale;
	r->ystep = mlx->_m.map_scale * tan(ray->ray_angle);
	r->x_inter = floor(mlx->_p.player_x / mlx->_m.map_scale) * mlx->_m.map_scale;
	if ((ray->ray_angle < M_PI / 2 || ray->ray_angle > 1.5 * M_PI)) // facing right
		r->x_inter += mlx->_m.map_scale; 
	else 
		r->xstep *= -1;
	if (r->ystep < 0 && (ray->ray_angle < M_PI && ray->ray_angle > 0))
		r->ystep *= -1;
	if (r->ystep > 0 && !(ray->ray_angle < M_PI && ray->ray_angle > 0))
		r->ystep *= -1;
	r->y_inter = mlx->_p.player_y + ((r->x_inter - mlx->_p.player_x) * tan(ray->ray_angle));
	
	if (!(ray->ray_angle < M_PI / 2 || ray->ray_angle > 1.5 * M_PI))
		r->x_inter--;
	hit_distance = get_distance(mlx, r);
	return (hit_distance);
}

float	cast(t_ray *ray, t_mlx *mlx)
{
	float	distance_to_wall;
	float ver_distance;
	float hor_distance;
	t_inter r[2];

	ver_distance = vertical_hit(mlx, ray , &r[0]);
	hor_distance = horizontal_hit(mlx, ray ,&r[1]);
	if (hor_distance < ver_distance)
	{
		ray->hit_side = HORIZONTAL;
		distance_to_wall = hor_distance;
		ray->hit_point[X] = r[1].hit_x;
		ray->hit_point[Y] = r[1].hit_y;
	}
	else
	{
		ray->hit_side = VERTICAL;
		distance_to_wall = ver_distance;
		ray->hit_point[X] = r[0].hit_x;
		ray->hit_point[Y] = r[0].hit_y;
	}
	distance_to_wall *= cos(mlx->_p.player_angle - ray->ray_angle);
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
		color = shader(WHITE, 50 );
	if (ray->hit_point[X] - mlx->_p.player_x >= 0 && ray->hit_side == VERTICAL)
		color = shader(0x00505652, 40 );
	return (color);
}

int	hit_wall(t_mlx *mlx, t_ray *ray, int i)
{
	ray->x = floor(cos(ray->ray_angle) * i) + mlx->_p.player_x;
	if (mlx->_m.map[(int)ray->y / mlx->_m.map_scale][(int)ray->x
		/ mlx->_m.map_scale] == '1')
		return (1);
	ray->y = floor(sin(ray->ray_angle) * i) + (mlx->_p.player_y);
	if (mlx->_m.map[(int)ray->y / mlx->_m.map_scale][(int)ray->x
		/ mlx->_m.map_scale] == '1')
		return (1);
	return (0);
}

void	draw_ray(t_mlx *mlx, t_ray *ray)
{
	if (mlx->_m.display_map > 0)
	{
		if (ray->x  < mlx->_p.player_x
			+ 100 && (ray->y  < mlx->_p.player_y + 100))
			my_mlx_pixel_put(mlx, ray->x , ray->y, RAYCOLOR);
	}
	else
		my_mlx_pixel_put(mlx, ray->x , ray->y , RAYCOLOR);
}

void drawline(t_mlx *mlx , float  ray_angle)
{
	int		i;
	t_ray	ray;

	ray.ray_angle = ray_angle;
	i = 0;
	ray.x = (cos(ray.ray_angle) * i) + mlx->_p.player_x ;
	ray.y = (sin(ray.ray_angle) * i) + mlx->_p.player_y;
	while (1)
	{
		draw_ray(mlx, &ray);
		if (hit_wall(mlx, &ray, i))
			break ;
		i++;
	}
	printf ("i == %d" , i);
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
	drawline(mlx, mlx->_p.player_angle - 0.1);
	drawline(mlx, mlx->_p.player_angle);
	drawline(mlx, mlx->_p.player_angle + 0.1);
}
