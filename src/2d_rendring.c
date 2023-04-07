/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2d_rendring.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 22:59:47 by del-khay          #+#    #+#             */
/*   Updated: 2023/04/07 03:51:52 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

int hit_wall(t_mlx *mlx, float x, float y, t_inter *r)
{
	if (x / mlx->_m.map_scale < 0 || x / mlx->_m.map_scale > mlx->_m.map_width
		|| y / mlx->_m.map_scale < 0 || y / mlx->_m.map_scale > mlx->_m.map_height)
		return (1);
	if (mlx->_m.map[(int)(y / mlx->_m.map_scale)][(int)(x / mlx->_m.map_scale)] == 'D')
	{
		r->door_x = x;
		r->door_y = y;
	};
	if (mlx->_m.map[(int)(y / mlx->_m.map_scale)][(int)(x / mlx->_m.map_scale)] == '1')
			return (1);
	return (0);
}
float get_distance(t_mlx *mlx, t_inter *r ,t_ray *ray, int side)
{
	float hit_distance;

	while (1)
	{
		if (r->x_inter < 0 || r->x_inter > mlx->_m.map_width * mlx->_m.map_scale
			|| r->y_inter < 0 || r->y_inter > mlx->_m.map_height * mlx->_m.map_scale)
			break ;
		if (r->y_inter / mlx->_m.map_scale >= mlx->_m.map_height
			|| r->x_inter / mlx->_m.map_scale >= mlx->_m.map_width)
			break ;
		if (side == HORIZONTAL)
		{
				if (!(ray->ray_angle < M_PI && ray->ray_angle > 0))
				{
					if(hit_wall(mlx, r->x_inter, r->y_inter - 1, r))
						break ;
				}
				else
				{
					if(hit_wall(mlx, r->x_inter, r->y_inter, r))
						break ;
				}
		}
		if (side == VERTICAL)
		{
			if (!(ray->ray_angle < M_PI / 2 || ray->ray_angle > 1.5 * M_PI))
			{
				if(hit_wall(mlx, r->x_inter - 1, r->y_inter, r))
					break ;
			}
			else
			{
				if(hit_wall(mlx, r->x_inter, r->y_inter, r))
					break ;
			}
		}
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
	if (isnan(r->x_inter))
		r->x_inter = 0;
	hit_distance = get_distance(mlx, r, ray, HORIZONTAL);
	return (hit_distance);
}

float vertical_hit(t_mlx *mlx , t_ray *ray , t_inter *r)
{
	float   hit_distance;
	
	ray->ray_angle = remainder(ray->ray_angle ,(2 * M_PI));
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
	hit_distance = get_distance(mlx, r, ray, VERTICAL);
	return (hit_distance);
}

float	cast(t_ray *ray, t_mlx *mlx)
{
	float	distance_to_wall;
	float ver_distance;
	float hor_distance;
	t_inter r[2];

	r[0].x_inter = 0;
	r[0].y_inter = 0;
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
	ray->step = mlx->fov / ray->rays_number;
}

t_side	get_color(t_ray *ray, t_mlx *mlx )
{
	float floored_x;
	float floored_y;
	int x; // for the door
	int y; // for the door
	t_side info;
	
	floored_x = floor(ray->hit_point[X] / mlx->_m.map_scale) * mlx->_m.map_scale;
	floored_y = floor(ray->hit_point[Y] / mlx->_m.map_scale) * mlx->_m.map_scale;
	x = ray->hit_point[X] / mlx->_m.map_scale;
	y = ray->hit_point[Y] / mlx->_m.map_scale;
	info.x = 0;
	if (ray->hit_point[Y] - mlx->_p.player_y < 0 && ray->hit_side == HORIZONTAL)
	{
		if (mlx->_m.map[y - 1][x] == 'D')
		{
			info.tex = DR;
			info.x = ((ray->hit_point[X] - floored_x)  / mlx->_m.map_scale) * mlx->_t[DR].width;
		}
		else
		{
			info.tex = NO;
			info.x = ((ray->hit_point[X] - floored_x)  / mlx->_m.map_scale) * mlx->_t[NO].width;
		}
	}
	if (ray->hit_point[Y] - mlx->_p.player_y >= 0 && ray->hit_side == HORIZONTAL)
	{
		if (mlx->_m.map[y][x] == 'D')
		{
			info.tex = DR;
			info.x = ((ray->hit_point[X] - floored_x)/ mlx->_m.map_scale) *  mlx->_t[DR].width;
			info.x = mlx->_t[DR].width - info.x  - 1;
		}
		else
		{
			info.tex = SO;
			info.x = ((ray->hit_point[X] - floored_x)/ mlx->_m.map_scale) *  mlx->_t[SO].width;
			info.x = mlx->_t[SO].width - info.x  - 1;
		}
	}
	if (ray->hit_point[X] - mlx->_p.player_x < 0 && ray->hit_side == VERTICAL)
	{
		if (mlx->_m.map[y][x - 1] == 'D')
		{
			info.tex = DR;
			info.x = ((ray->hit_point[Y] - floored_y)  / mlx->_m.map_scale) *  mlx->_t[DR].width;
			info.x = mlx->_t[DR].width - info.x - 1;
		}
		else
		{
			info.tex = WE;
			info.x = ((ray->hit_point[Y] - floored_y)  / mlx->_m.map_scale) *  mlx->_t[WE].width;
			info.x = mlx->_t[WE].width - info.x - 1;
		}
	}
	if (ray->hit_point[X] - mlx->_p.player_x >= 0 && ray->hit_side == VERTICAL)
	{
		if (mlx->_m.map[y][x] == 'D')
		{
			info.tex = DR;
			info.x = ((ray->hit_point[Y] - floored_y)  / mlx->_m.map_scale) *  mlx->_t[DR].width;
		}
		else
		{
			info.tex = EA;
			info.x = ((ray->hit_point[Y] - floored_y)  / mlx->_m.map_scale) *  mlx->_t[EA].width;
		}
	}
	return (info);
}

void	draw_ray(t_mlx *mlx, t_ray *ray)
{
	if (mlx->_m.display_map > 0)
	{
		if (ray->x  < mlx->_p.player_x
			+ 100 && (ray->y  < mlx->_p.player_y + 100))
			my_mlx_pixel_put(mlx, ray->x , ray->y, 0x00FF0000);
	}
	else
		my_mlx_pixel_put(mlx, ray->x , ray->y , 0x00FF0000);
}

void	ray_caster(t_mlx *mlx)
{
	t_ray	ray;
	int		i;

	init_ray(&ray, mlx);
	i = 0;
	while (i  < ray.rays_number)
	{
		mlx->distances[i] = cast(&ray, mlx);
		if (mlx->_m.display_map > 0)
		{
			if (ray.hit_point[X]  < mlx->_p.player_x
				+ 100 && (ray.hit_point[Y]  < mlx->_p.player_y + 100))
			{
				my_mlx_pixel_put(mlx, ray.hit_point[X] , ray.hit_point[Y], WHITE);
				my_mlx_pixel_put(mlx, ray.hit_point[X] - 1, ray.hit_point[Y] - 1, 0x9D00FF);
				my_mlx_pixel_put(mlx, ray.hit_point[X] + 1, ray.hit_point[Y] + 1, 0x9D00FF);
			}
		}
	else
	{
			my_mlx_pixel_put(mlx, ray.hit_point[X], ray.hit_point[Y], WHITE);
			my_mlx_pixel_put(mlx, ray.hit_point[X] - 1, ray.hit_point[Y] - 1, 0x9D00FF);
			my_mlx_pixel_put(mlx, ray.hit_point[X] + 1, ray.hit_point[Y] + 1, 0x9D00FF);
	}
		mlx->_s[i] = get_color(&ray, mlx);
		ray.ray_angle += ray.step;
		i++;
	}
}