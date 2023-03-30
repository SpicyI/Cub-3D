/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2drendring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 22:59:47 by del-khay          #+#    #+#             */
/*   Updated: 2023/03/30 04:34:47 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

void	putPlayer(t_mlx *mlx)
{
	int	y;
	int	player_thickness;
	int x;

	x = 0;
	y = 0;
	player_thickness = 30;
	x = (mlx->_m.img_xpos + mlx->_p.player_x) - player_thickness / 2;
	y = (mlx->_m.img_ypos + + mlx->_p.player_y) - player_thickness / 2;
	mlx_put_image_to_window(mlx->p_mlx, mlx->win, mlx->_p.icon_img, x, y);
}

void crop_img(t_mlx *mlx , int x , int y)
{
	int reset_y;
	
	reset_y = y;
	while (x < mlx->_m.map_width * mlx->_m.map_scale)
	{
		y = reset_y;
		while (y < mlx->_m.map_height * mlx->_m.map_scale)
		{
			my_mlx_pixel_put(mlx, x, y, TRANSPARENT);
			y++;
		}
		x++;
	}
}

void draw_bloc(t_mlx *mlx , t_bloc *t)
{
	if (mlx->_m.map[t->y][t->x] != '1')
	{
		if ((t->bloc_y + 1 == (t->y + 1) * mlx->_m.map_scale && (t->y
					+ 1 < mlx->_m.map_height && mlx->_m.map[t->y
					+ 1][t->x] == '1')) ||
			(t->bloc_x + 1 == (t->x + 1) * mlx->_m.map_scale && (t->x
						+ 1 < mlx->_m.map_width
						&& mlx->_m.map[t->y][t->x + 1] == '1')))
			my_mlx_pixel_put(mlx, t->bloc_x, t->bloc_y, WHITE);
		else
			my_mlx_pixel_put(mlx, t->bloc_x, t->bloc_y, FLOORCOLOR);
	}
	else
	{
		if ((t->bloc_y + 1 == (t->y + 1) * mlx->_m.map_scale && (t->y
					+ 1 < mlx->_m.map_height && mlx->_m.map[t->y
					+ 1][t->x] != '1')) ||
			(t->bloc_x + 1 == (t->x + 1) * mlx->_m.map_scale && (t->x
						+ 1 < mlx->_m.map_width
						&& mlx->_m.map[t->y][t->x + 1] != '1')))
			my_mlx_pixel_put(mlx, t->bloc_x, t->bloc_y, WHITE);
		else
			my_mlx_pixel_put(mlx, t->bloc_x, t->bloc_y, WALLCOLOR);
	}
}

void iterate_map(t_mlx *mlx , t_bloc *t)
{
	while (t->y < mlx->_m.map_height)
	{
		t->x = 0;
		while (t->x < mlx->_m.map_width)
		{
			t->bloc_y = t->y * mlx->_m.map_scale;
			t->bloc_x = t->x * mlx->_m.map_scale;
			while (t->bloc_y < (t->y + 1) * mlx->_m.map_scale)
			{
				while (t->bloc_x < (t->x + 1) * mlx->_m.map_scale)
				{
					draw_bloc(mlx, t);
					t->bloc_x++;
				}
				t->bloc_x = t->x * mlx->_m.map_scale;
				t->bloc_y++;
			}
			t->x++;
		}
		t->y++;
	}
}
void	drawMap(t_mlx *mlx)
{
	t_bloc t;

	t.bloc_y = 0;
	t.bloc_x = 0;
	mlx->img = mlx_new_image(mlx->p_mlx, mlx->_m.map_width * mlx->_m.map_scale,
			mlx->_m.map_height * mlx->_m.map_scale);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel,
			&mlx->line_length, &mlx->endian);
	t.y = 0;
	iterate_map(mlx, &t);
	if (mlx->_m.display_map > 0)
	{
		crop_img(mlx, mlx->_p.player_x + 100, 0);
		crop_img(mlx, 0, mlx->_p.player_y + 100);
	}
	mlx->_m.map_img = mlx->img;
	mlx->_m.mapimg_addr = mlx->addr;
}

void draw_ray(t_mlx *mlx , t_ray *ray)
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
	float distanceToWall;

	ray->hit_point[X] = (ray->x / ray->scale_factor) * mlx->_m.map_scale;
	ray->hit_point[Y] = (ray->y / ray->scale_factor) * mlx->_m.map_scale;
	distanceToWall = sqrt(pow(ray->x - ((mlx->_p.player_x / mlx->_m.map_scale)
					* ray->scale_factor), 2) + pow(ray->y - ((mlx->_p.player_y
						/ mlx->_m.map_scale) * ray->scale_factor), 2));
	distanceToWall *= cos(mlx->_p.player_angle - ray->ray_angle);
	return (distanceToWall);
}

int hit_wall(t_mlx * mlx,t_ray *ray, int i)
{
	ray->x = floor((cos(ray->ray_angle) * i) + (((mlx->_p.player_x / mlx->_m.map_scale)
				* ray->scale_factor)));
	if (mlx->_m.map[(int)ray->y / SCALEFACTOR][(int)ray->x / SCALEFACTOR] == '1')
	{
		ray->hit_side = VERTICAL;
		return (1) ;
	}
	ray->y = floor((sin(ray->ray_angle) * i) + ((mlx->_p.player_y / mlx->_m.map_scale)
				* ray->scale_factor));
	if (mlx->_m.map[(int)ray->y / SCALEFACTOR][(int)ray->x / SCALEFACTOR] == '1')
	{
		ray->hit_side = HORIZONTAL;
		return (1) ;
	}
	return (0);
}
float	cast(t_ray *ray, t_mlx *mlx)
{
	int		i;
	float	distanceToWall;

	i = 0;
	ray->x = (cos(ray->ray_angle) * i) + ((mlx->_p.player_x / mlx->_m.map_scale)
				* ray->scale_factor);
	ray->y = (sin(ray->ray_angle) * i) + ((mlx->_p.player_y / mlx->_m.map_scale)
				* ray->scale_factor);
	while (1)
	{
		draw_ray(mlx, ray);
		if (hit_wall(mlx,ray, i))
			break ;
		i++;
	}
	distanceToWall = calculate_distance(mlx, ray);
	return (distanceToWall);
}
void	initRay(t_ray *ray, t_mlx *mlx)
{
	ray->ray_angle = mlx->_p.player_angle - (mlx->fov / 2);
	ray->max_angle = mlx->_p.player_angle + (mlx->fov / 2);
	ray->rays_number = RAYNUMBER;
	ray->scale_factor = SCALEFACTOR;
	ray->step = mlx->fov / ray->rays_number;
}

int	getColor(t_ray *ray, t_mlx *mlx)
{
	int	color;

	color = 0;
	if (ray->hit_point[Y] - mlx->_p.player_y < 0 && ray->hit_side == HORIZONTAL)
		color = 0x00555652; // green for north
	if (ray->hit_point[Y] - mlx->_p.player_y >= 0
		&& ray->hit_side == HORIZONTAL)
		color = METAL; // red for south
	if (ray->hit_point[X] - mlx->_p.player_x < 0 && ray->hit_side == VERTICAL)
		color = shader(WHITE, 50); // blue for east
	if (ray->hit_point[X] - mlx->_p.player_x >= 0 && ray->hit_side == VERTICAL)
		color = shader(0x00505652, 40); // yellow for west
	return (color);
}

void	rayCaster(t_mlx *mlx)
{
	t_ray	ray;
	int		i;

	initRay(&ray, mlx);
	i = 0;
	while (i < ray.rays_number)
	{
		mlx->distances[i] = cast(&ray, mlx);
		mlx->ray_color[i] = getColor(&ray, mlx);
		ray.ray_angle += ray.step;
		i++;
	}
}

void	transparent_Bg(t_mlx *mlx, int img_width, int img_height)
{
	int	x;
	int	y;

	x = 0;
	while (x < img_width)
	{
		y = 0;
		while (y < img_height)
		{
			my_mlx_pixel_put(mlx, x, y, TRANSPARENT);
			y++;
		}
		x++;
	}
}

// This function calculates the final color of a pixel based on the color of the pixel itself and the percentage of transparency of the pixel.
// The function takes in the color of the pixel and the percentage of transparency of the pixel.

int	shader(int color, int shad_percentage)
{
	unsigned char	full_transparency;
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;

	full_transparency = 255;
	red = (color >> 16) & 0xFF;
	green = (color >> 8) & 0xFF;
	blue = color & 0xFF;
	if (shad_percentage > 100)
		shad_percentage = 100;
	full_transparency -= full_transparency * shad_percentage / 100;
	return (full_transparency << 24 | red << 16 | green << 8 | blue);
}

void	putWalls(t_mlx *mlx)
{
	int		x;
	int		y;
	int		i;
	int		wallHeight;
	t_mlx	tmp;

	x = 0;
	y = 0;
	i = 0;
	tmp.img = mlx_new_image(mlx->p_mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	tmp.addr = mlx_get_data_addr(tmp.img, &tmp.bits_per_pixel, &tmp.line_length,
			&mlx->endian);
	// fill the screen column by column
	while (x < SCREEN_WIDTH)
	{
		// calculate the wall height
		wallHeight = (SCALEFACTOR / mlx->distances[(int)(x * 0.4 )]) * mlx->sreen_dist;
		if (wallHeight >= SCREEN_HEIGHT)
			wallHeight = SCREEN_HEIGHT;
		i = 0;
		// offset the middle of the screen
		y = (SCREEN_HEIGHT / 2) - (wallHeight / 2);
		// draw the ceiling
		while (i < y)
		{
			my_mlx_pixel_put(&tmp, x, i, shader(SKYCOLOR, ((SCREEN_HEIGHT / 2)
							- i) * 100 / (SCREEN_HEIGHT / 2)));
			i++;
		}
		// draw the floor
		i += wallHeight;
		while (i < SCREEN_HEIGHT)
		{
			my_mlx_pixel_put(&tmp, x, i, shader(GROUNDCOLOR, (i - (SCREEN_HEIGHT
								/ 2)) * 100 / (SCREEN_HEIGHT / 2)));
			i++;
		}
		i = 0;
		// draw the wall strip
		while (i < wallHeight)
		{
			my_mlx_pixel_put(&tmp, x, y + i, shader(mlx->ray_color[(int)(x * 0.4)], wallHeight * 400
						/ SCREEN_HEIGHT));
			i++;
		}
		x++;
	}
	mlx_put_image_to_window(mlx->p_mlx, mlx->win, tmp.img, 0, 0);
	mlx_destroy_image(mlx->p_mlx, tmp.img);
}
