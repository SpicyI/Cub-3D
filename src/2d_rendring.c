/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2d_rendring.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 22:59:47 by del-khay          #+#    #+#             */
/*   Updated: 2023/04/08 04:44:02 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

void	init_ray(t_ray *ray, t_mlx *mlx)
{
	ray->ray_angle = mlx->_p.player_angle - (mlx->fov / 2);
	ray->max_angle = mlx->_p.player_angle + (mlx->fov / 2);
	ray->rays_number = RAYNUMBER;
	ray->step = mlx->fov / ray->rays_number;
}

t_side	set_side(float *p, float *floored_p, t_ray *ray, t_mlx *m)
{
	t_side	info;

	if (p[Y] - m->_p.player_y < 0 && ray->hit_side == HOR)
	{
		info.tex = NO;
		info.x = ((p[X] - floored_p[X]) / m->_m.map_scale) * m->_t[NO].width;
	}
	if (p[Y] - m->_p.player_y >= 0 && ray->hit_side == HOR)
	{
		info.tex = SO;
		info.x = ((p[X] - floored_p[X]) / m->_m.map_scale) * m->_t[SO].width;
		info.x = m->_t[SO].width - info.x - 1;
	}
	if (p[X] - m->_p.player_x < 0 && ray->hit_side == VER)
	{
		info.tex = WE;
		info.x = ((p[Y] - floored_p[Y]) / m->_m.map_scale) * m->_t[WE].width;
		info.x = m->_t[WE].width - info.x - 1;
	}
	if (p[X] - m->_p.player_x >= 0 && ray->hit_side == VER)
	{
		info.tex = EA;
		info.x = ((p[Y] - floored_p[Y]) / m->_m.map_scale) * m->_t[EA].width;
	}
	return (info);
}

t_side	get_color(t_ray *ray, t_mlx *mlx)
{
	float	floored_p[2];
	float	p[2];
	t_side	info;

	p[X] = ray->hit_point[X];
	p[Y] = ray->hit_point[Y];
	floored_p[X] = floor(p[X] / mlx->_m.map_scale) * mlx->_m.map_scale;
	floored_p[Y] = floor(p[Y] / mlx->_m.map_scale) * mlx->_m.map_scale;
	info = set_side(p, floored_p, ray, mlx);
	return (info);
}

void	highlight_hit_point(t_mlx *mlx, t_ray *ray)
{
	int	x;
	int	y;

	x = ray->hit_point[X];
	y = ray->hit_point[Y];
	if (mlx->_m.display_map > 0)
	{
		if (x < mlx->_p.player_x + 100 && (y < mlx->_p.player_y + 100))
		{
			my_mlx_pixel_put(mlx, x, y, WHITE);
			my_mlx_pixel_put(mlx, x - 1, y - 1, PURPLE);
			my_mlx_pixel_put(mlx, x + 1, y + 1, PURPLE);
		}
	}
	else
	{
		my_mlx_pixel_put(mlx, x, y, WHITE);
		my_mlx_pixel_put(mlx, x - 1, y - 1, PURPLE);
		my_mlx_pixel_put(mlx, x + 1, y + 1, PURPLE);
	}
}

void	ray_caster(t_mlx *mlx)
{
	t_ray	ray;
	int		i;

	init_ray(&ray, mlx);
	i = 0;
	while (i < ray.rays_number)
	{
		mlx->distances[i] = cast(&ray, mlx, i);
		highlight_hit_point(mlx, &ray);
		mlx->_s[i] = get_color(&ray, mlx);
		ray.ray_angle += ray.step;
		i++;
	}
}
