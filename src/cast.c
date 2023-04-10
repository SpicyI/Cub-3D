/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 04:39:44 by del-khay          #+#    #+#             */
/*   Updated: 2023/04/09 03:37:45 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

void	init_inter(t_inter *r)
{
	r[0].x_inter = 0;
	r[0].y_inter = 0;
	r[0].hit_door = 0;
	r[1].hit_door = 0;
	r[0].hit_sprite = 0;
	r[1].hit_sprite = 0;
}

void	door_detetction(t_mlx *mlx, t_inter *r, t_ray *ray, int i)
{
	t_inter	t;

	mlx->_d[i].door_exist = 0;
	t = rmin(r[0], r[1]);
	mlx->_d[i].door_dist = t.door_dest * cos(mlx->_p.player_angle
			- ray->ray_angle);
	mlx->_d[i].door_color = t.doorcolor;
	if (mlx->_d[i].door_dist < ray->dist)
		mlx->_d[i].door_exist = 1;
}

float	horizontal_hit(t_mlx *mlx, t_ray *ray, t_inter *r)
{
	float	hit_distance;

	r->ystep = mlx->_m.map_scale;
	r->xstep = mlx->_m.map_scale / tan(ray->ray_angle);
	r->y_inter = floor(mlx->_p.player_y / mlx->_m.map_scale)
		* mlx->_m.map_scale;
	if (ray->ray_angle < M_PI && ray->ray_angle > 0)
		r->y_inter += mlx->_m.map_scale;
	else
		r->ystep *= -1;
	if (r->xstep < 0 && (ray->ray_angle < M_PI / 2 || ray->ray_angle > 1.5
			* M_PI))
		r->xstep *= -1;
	if (r->xstep > 0 && !(ray->ray_angle < M_PI / 2 || ray->ray_angle > 1.5
			* M_PI))
		r->xstep *= -1;
	r->x_inter = mlx->_p.player_x + ((r->y_inter - mlx->_p.player_y)
			/ tan(ray->ray_angle));
	if (isnan(r->x_inter))
		r->x_inter = 0;
	hit_distance = get_distance(mlx, r, ray, HORIZONTAL);
	return (hit_distance);
}

float	vertical_hit(t_mlx *mlx, t_ray *ray, t_inter *r)
{
	float	hit_distance;

	ray->ray_angle = remainder(ray->ray_angle, (2 * M_PI));
	if (ray->ray_angle < 0)
		ray->ray_angle += (2 * M_PI);
	r->xstep = mlx->_m.map_scale;
	r->ystep = mlx->_m.map_scale * tan(ray->ray_angle);
	r->x_inter = floor(mlx->_p.player_x / mlx->_m.map_scale)
		* mlx->_m.map_scale;
	if ((ray->ray_angle < M_PI / 2 || ray->ray_angle > 1.5 * M_PI))
		r->x_inter += mlx->_m.map_scale;
	else
		r->xstep *= -1;
	if (r->ystep < 0 && (ray->ray_angle < M_PI && ray->ray_angle > 0))
		r->ystep *= -1;
	if (r->ystep > 0 && !(ray->ray_angle < M_PI && ray->ray_angle > 0))
		r->ystep *= -1;
	r->y_inter = mlx->_p.player_y + ((r->x_inter - mlx->_p.player_x)
			* tan(ray->ray_angle));
	hit_distance = get_distance(mlx, r, ray, VERTICAL);
	if (!r->hit_door)
		r->door_dest = hit_distance;
	if (!r->hit_sprite)
		r->sprite_dist = hit_distance;
	return (hit_distance);
}

float	cast(t_ray *ray, t_mlx *mlx, int i)
{
	float	ver_distance;
	float	hor_distance;
	t_inter	r[2];

	init_inter(r);
	ver_distance = vertical_hit(mlx, ray, &r[0]);
	hor_distance = horizontal_hit(mlx, ray, &r[1]);
	if (hor_distance < ver_distance)
	{
		ray->hit_side = HORIZONTAL;
		ray->dist = hor_distance;
		ray->hit_point[X] = r[1].hit_x;
		ray->hit_point[Y] = r[1].hit_y;
	}
	else
	{
		ray->hit_side = VERTICAL;
		ray->dist = ver_distance;
		ray->hit_point[X] = r[0].hit_x;
		ray->hit_point[Y] = r[0].hit_y;
	}
	ray->dist *= cos(mlx->_p.player_angle - ray->ray_angle);
	door_detetction(mlx, r, ray, i);
	sprite_detection(mlx, r, ray, i);
	return (ray->dist);
}
