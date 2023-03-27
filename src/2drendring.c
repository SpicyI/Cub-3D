/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2drendring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 22:59:47 by del-khay          #+#    #+#             */
/*   Updated: 2023/03/27 20:31:31 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

void	putPlayer(t_mlx *mlx)
{
	int	y;
	int	player_thickness;

	int x = 0; // start of the rectangle (player)
	y = 0;
	player_thickness = 6;
	mlx->img = mlx_new_image(mlx->p_mlx, mlx->_m.mapWidth * mlx->_m.mapScale,
			mlx->_m.mapHeight * mlx->_m.mapScale);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel,
			&mlx->line_length, &mlx->endian);
	// draw the transparent background
	transparent_Bg(mlx);
	// Draw the player
	x = mlx->_p.playerX - player_thickness / 2;
	while (x < mlx->_p.playerX + player_thickness / 2)
	{
		y = mlx->_p.playerY - 3;
		while (y < mlx->_p.playerY + player_thickness / 2)
		{
			my_mlx_pixel_put(mlx, x, y, 0x20FFFF00);
			y++;
		}
		x++;
	}
	// Draw the player
	mlx_put_image_to_window(mlx->p_mlx, mlx->win, mlx->img, (screenWidth / 2)
			- (mlx->_m.mapWidth * mlx->_m.mapScale / 2), (screenHeight / 2)
			- (mlx->_m.mapHeight * mlx->_m.mapScale / 2));
	// mlx_put_image_to_window(mlx->p_mlx, mlx->win, mlx->img, 0, 0);
	mlx_destroy_image(mlx->p_mlx, mlx->img);
}

void	drawMap(t_mlx *mlx)
{
	int	x;
	int	y;
	int	i;
	int	j;

	i = 0;
	j = 0;
	// int playerprojectionx = (mlx->_p.playerX / mlx->_m.mapScale);
	// int playerprojectiony = (mlx->_p.playerY / mlx->_m.mapScale);
	mlx->img = mlx_new_image(mlx->p_mlx, screenWidth, screenHeight);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel,
			&mlx->line_length, &mlx->endian);
	y = 0;
	// y = playerprojectiony - 4;
	// if (y < 0)
	//     y = 0;
	// if (y > mlx->_m.mapHeight)
	//     y = mlx->_m.mapHeight;
	while (y < mlx->_m.mapHeight)
	{
		x = 0;
		// x = playerprojectionx - 4;
		// if (x < 0)
		//     x = 0;
		// if (x > mlx->_m.mapWidth)
		//     x = mlx->_m.mapWidth;
		while (x < mlx->_m.mapWidth)
		{
			// we set block dementions
			i = y * mlx->_m.mapScale;
			j = x * mlx->_m.mapScale;
			// we draw the block
			while (i + 1 < (y + 1) * mlx->_m.mapScale)
			{
				while (j + 1 < (x + 1) * mlx->_m.mapScale)
				{
					if (mlx->_m.map[y][x] == '1')
						my_mlx_pixel_put(mlx, j, i, WALLCOLOR); // draw the wall
					else
						my_mlx_pixel_put(mlx, j, i, FLOORCOLOR);
					// draw the floor
					j++;
				}
				// we reset the x axis
				j = x * mlx->_m.mapScale;
				i++;
			}
			x++;
		}
		y++;
	}
	mlx->_m.mapImg = mlx->img;
	mlx->_m.mapImgAddr = mlx->addr;
}

void	putDirection(t_mlx *mlx)
{
	int	x;
	int	y;
	int	line_length;
	int	i;

	x = 0;
	y = 0;
	line_length = mlx->_m.mapScale / 2;
	i = 0;
	mlx->img = mlx_new_image(mlx->p_mlx, mlx->_m.mapWidth * mlx->_m.mapScale,
			mlx->_m.mapHeight * mlx->_m.mapScale);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel,
			&mlx->line_length, &mlx->endian);
	// draw the transparent background
	transparent_Bg(mlx);
	// Draw the line
	while (i < line_length)
	{
		x = (cos(mlx->_p.playerAngle) * i) + mlx->_p.playerX;
		y = (sin(mlx->_p.playerAngle) * i) + mlx->_p.playerY;
		my_mlx_pixel_put(mlx, x, y, ARROWCOLOR);
		i++;
	}
	mlx_put_image_to_window(mlx->p_mlx, mlx->win, mlx->img, (screenWidth / 2)
			- (mlx->_m.mapWidth * mlx->_m.mapScale / 2), (screenHeight / 2)
			- (mlx->_m.mapHeight * mlx->_m.mapScale / 2));
	mlx_destroy_image(mlx->p_mlx, mlx->img);
}

float	cast(float rayAngle, t_mlx *mlx)
{
	int		x;
	int		y;
	int		i;
	float	distanceToWall;

	i = 0;
	x = floor((cos(rayAngle) * i) + mlx->_p.playerX);
	y = floor((sin(rayAngle) * i) + mlx->_p.playerY);
	// cast the ray
	while (1)
	{
		my_mlx_pixel_put(mlx, x, y, RAYCOLOR);
		x = floor((cos(rayAngle) * i) + mlx->_p.playerX);
		if (mlx->_m.map[y / mlx->_m.mapScale][x / mlx->_m.mapScale] == '1')
			break ;
		y = floor((sin(rayAngle) * i) + mlx->_p.playerY);
		if (mlx->_m.map[y / mlx->_m.mapScale][x / mlx->_m.mapScale] == '1')
			break ;
		i++;
	}
	// calculate the distance and return it
	distanceToWall = sqrt(pow(x - mlx->_p.playerX, 2) + pow(y - mlx->_p.playerY,
				2));
	// correct the distance
	distanceToWall *= cos(mlx->_p.playerAngle - rayAngle);
	return (distanceToWall);
}

void	rayCaster(t_mlx *mlx)
{
	t_ray	ray;
	int		i;

	mlx->img = mlx_new_image(mlx->p_mlx, mlx->_m.mapWidth * mlx->_m.mapScale,
			mlx->_m.mapHeight * mlx->_m.mapScale);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel,
			&mlx->line_length, &mlx->endian);
	// draw the transparent background
	transparent_Bg(mlx);
	// set the ray
	ray.startAngle = mlx->_p.playerAngle - (FOV / 2);
	ray.endAngle = mlx->_p.playerAngle + (FOV / 2);
	ray.rayNumber = RAYNUMBER;
	ray.step = FOV / ray.rayNumber;
	i = 0;
	// cast the rays
	while (i < ray.rayNumber)
	{
		mlx->distances[i] = cast(ray.startAngle, mlx);
		ray.startAngle += ray.step;
		i++;
	}
	mlx_put_image_to_window(mlx->p_mlx, mlx->win, mlx->img, (screenWidth / 2)
			- (mlx->_m.mapWidth * mlx->_m.mapScale / 2), (screenHeight / 2)
			- (mlx->_m.mapHeight * mlx->_m.mapScale / 2));
	mlx_destroy_image(mlx->p_mlx, mlx->img);
}

void	transparent_Bg(t_mlx *mlx)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x < screenWidth)
	{
		y = 0;
		while (y < screenHeight)
		{
			my_mlx_pixel_put(mlx, x, y, TRANSPARENT);
			y++;
		}
		x++;
	}
}

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

void	put_landscape(t_mlx *mlx)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	mlx->img = mlx_new_image(mlx->p_mlx, screenWidth, screenHeight);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel,
			&mlx->line_length, &mlx->endian);
	while (y < screenHeight / 2)
	{
		x = 0;
		while (x < screenWidth)
		{
			my_mlx_pixel_put(mlx, x, y, SKYCOLOR);
			x++;
		}
		y++;
	}
	while (y < screenHeight)
	{
		x = 0;
		while (x < screenWidth)
		{
			my_mlx_pixel_put(mlx, x, y, GROUNDCOLOR);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mlx->p_mlx, mlx->win, mlx->img, 0, 0);
	mlx_destroy_image(mlx->p_mlx, mlx->img);
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
	tmp.img = mlx_new_image(mlx->p_mlx, screenWidth, screenHeight);
	tmp.addr = mlx_get_data_addr(tmp.img, &tmp.bits_per_pixel, &tmp.line_length,
			&mlx->endian);
	// fill the screen column by column
	while (x < screenWidth)
	{
		// calculate the wall height
		wallHeight = (mlx->_m.mapScale / mlx->distances[x]) * SCREEN_DIST;
		if (wallHeight >= screenHeight)
			wallHeight = screenHeight;
		i = 0;
		// offset the middle of the screen
		y = (screenHeight / 2) - (wallHeight / 2);
		// draw the ceiling
		while (i < y)
		{
			my_mlx_pixel_put(&tmp, x, i, shader(SKYCOLOR, ((screenHeight / 2)
							- i) * 100 / (screenHeight / 2)));
			i++;
		}
		i += wallHeight;
		// draw the floor
		while (i < screenHeight)
		{
			my_mlx_pixel_put(&tmp, x, i, shader(GROUNDCOLOR, (i - (screenHeight
								/ 2)) * 100 / (screenHeight / 2)));
			i++;
		}
		i = 0;
		// draw the wall strip
		while (i < wallHeight)
		{
			my_mlx_pixel_put(&tmp, x, y + i, shader(0x00a1a4a3, wallHeight * 300
						/ screenHeight));
			i++;
		}
		x++;
	}
	mlx_put_image_to_window(mlx->p_mlx, mlx->win, tmp.img, 0, 0);
	mlx_destroy_image(mlx->p_mlx, tmp.img);
}

// what is black in hexa
