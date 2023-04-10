/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 04:41:16 by del-khay          #+#    #+#             */
/*   Updated: 2023/04/10 00:37:30 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

int	hit_wall(t_mlx *mlx, float x, float y, t_inter *r)
{
	if (x < 0 || x > mlx->_m.map_width || y < 0 || y > mlx->_m.map_height)
		return (1);
	if (mlx->_m.map[(int)y][(int)x] == 'D' ||
		mlx->_m.map[(int)y][(int)x] == 'O')
	{
		if (!r->hit_door)
		{
			r->door_x = x * mlx->_m.map_scale;
			r->door_y = y * mlx->_m.map_scale;
			r->door_dest = sqrt(pow(mlx->_p.player_x - r->door_x, 2)
					+ pow(mlx->_p.player_y - r->door_y, 2));
			r->hit_door = 1;
			if (mlx->_m.map[(int)y][(int)x] == 'D')
				r->doorcolor = 0xBBFF0000;
			else if (mlx->_m.map[(int)y][(int)x] == 'O')
				r->doorcolor = 0xBB007FFF;
			my_mlx_pixel_put(mlx, x, y, 0x0000FF00);
		}
	}
	if (mlx->_m.map[(int)y][(int)x] == 'F')
		check_sprite(mlx, r, x, y);
	if (mlx->_m.map[(int)y][(int)x] == '1')
		return (1);
	return (0);
}

int	hit_structure(t_ray *ray, int side, t_mlx *mlx, t_inter *r)
{
	if (!(ray->ray_angle < M_PI && ray->ray_angle > 0) && side == HOR)
	{
		if (hit_wall(mlx, r->x_inter / mlx->_m.map_scale, (r->y_inter - 1)
				/ mlx->_m.map_scale, r))
			return (TRUE);
	}
	else if ((!(ray->ray_angle < M_PI / 2 || ray->ray_angle > 1.5 * M_PI))
		&& side == VER)
	{
		if (hit_wall(mlx, (r->x_inter - 1) / mlx->_m.map_scale, r->y_inter
				/ mlx->_m.map_scale, r))
			return (TRUE);
	}
	else if (hit_wall(mlx, r->x_inter / mlx->_m.map_scale, r->y_inter
			/ mlx->_m.map_scale, r))
		return (TRUE);
	return (FALSE);
}

float	get_distance(t_mlx *mlx, t_inter *r, t_ray *ray, int side)
{
	float	hit_distance;

	while (1)
	{
		if (r->x_inter < 0 || r->x_inter > mlx->_m.map_width * mlx->_m.map_scale
			|| r->y_inter < 0 || r->y_inter > mlx->_m.map_height
			* mlx->_m.map_scale)
			break ;
		if (r->y_inter / mlx->_m.map_scale >= mlx->_m.map_height || r->x_inter
			/ mlx->_m.map_scale >= mlx->_m.map_width)
			break ;
		if (hit_structure(ray, side, mlx, r))
			break ;
		r->x_inter += r->xstep;
		r->y_inter += r->ystep;
	}
	r->hit_x = r->x_inter;
	r->hit_y = r->y_inter;
	hit_distance = sqrt(pow(mlx->_p.player_x - r->x_inter, 2)
			+ pow(mlx->_p.player_y - r->y_inter, 2));
	if (!r->hit_door)
		r->door_dest = hit_distance;
	if (!r->hit_sprite)
		r->sprite_dist = hit_distance;
	return (hit_distance);
}
