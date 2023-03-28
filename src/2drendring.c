/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2drendring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 22:59:47 by del-khay          #+#    #+#             */
/*   Updated: 2023/03/28 04:47:49 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

void	putPlayer(t_mlx *mlx)
{
	int	y;
	int	player_thickness;

	int x = 0; // start of the rectangle (player)
	y = 0;
	player_thickness = 20;
	// Draw the player
	if (mlx->_m.displayMap < 0)
	{
		x = (screenWidth / 2) - (mlx->_m.mapWidth * mlx->_m.mapScale / 2) + mlx->_p.playerX  - player_thickness / 2;
		y = (screenHeight / 2) - (mlx->_m.mapHeight * mlx->_m.mapScale / 2) + mlx->_p.playerY - player_thickness / 2;
	}
	else
	{
		x = 100 - player_thickness / 2;
		y = 100 - player_thickness / 2;
	}
	mlx_put_image_to_window(mlx->p_mlx, mlx->win, mlx->_p.iconImg, x, y);
}

void	drawMap(t_mlx *mlx)
{
	int	x;
	int	y;
	int	i;
	int	j;

	i = 0;
	j = 0;
	mlx->img = mlx_new_image(mlx->p_mlx, mlx->_m.mapWidth * mlx->_m.mapScale,
			mlx->_m.mapHeight * mlx->_m.mapScale);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel,
			&mlx->line_length, &mlx->endian);
	y = 0;
	while (y < mlx->_m.mapHeight)
	{
		x = 0;
		while (x < mlx->_m.mapWidth)
		{
			// we set block dementions
			i = y * mlx->_m.mapScale;
			j = x * mlx->_m.mapScale;
			// we draw the block
			while (i < (y + 1) * mlx->_m.mapScale)
			{
				while (j < (x + 1) * mlx->_m.mapScale)
				{
					// if (mlx->_m.map[y][x] == '1')
					if (mlx->_m.map[y][x] != '1')
					{
						// add edges to map
						if ((i + 1 == (y + 1) * mlx->_m.mapScale && (y + 1 < mlx->_m.mapHeight && mlx->_m.map[y + 1][x] == '1')) ||
							(j + 1 == (x + 1) * mlx->_m.mapScale && (x + 1 < mlx->_m.mapWidth && mlx->_m.map[y][x + 1] == '1')))
							my_mlx_pixel_put(mlx, j, i, WHITE);
						else
						my_mlx_pixel_put(mlx, j, i, FLOORCOLOR);
					}
					// draw the floor
					else
					{
						// add edges to map
						if ((i + 1 == (y + 1) * mlx->_m.mapScale && (y + 1 < mlx->_m.mapHeight && mlx->_m.map[y + 1][x] != '1')) ||
							(j + 1 == (x + 1) * mlx->_m.mapScale && (x + 1 < mlx->_m.mapWidth && mlx->_m.map[y][x + 1] != '1')))
							my_mlx_pixel_put(mlx, j, i, WHITE);
						else
							my_mlx_pixel_put(mlx, j, i, WALLCOLOR);
						// draw the wall
					}
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
	// minimap system transparency
	if (mlx->_m.displayMap > 0)
	{
		x = mlx->_p.playerX + 100;
		y = 0;
		while (x < mlx->_m.mapWidth * mlx->_m.mapScale)
		{
			y = 0;
			while (y < mlx->_m.mapHeight * mlx->_m.mapScale)
			{
				my_mlx_pixel_put(mlx, x, y, TRANSPARENT);
				y++;
			}
			x++;
		}
		x = 0;
		y = mlx->_p.playerY + 100;
		while (x < mlx->_m.mapWidth * mlx->_m.mapScale)
		{
			y = mlx->_p.playerY + 100;
			while (y < mlx->_m.mapHeight * mlx->_m.mapScale)
			{
				my_mlx_pixel_put(mlx, x, y, TRANSPARENT);
				y++;
			}
			x++;
		}
	}
	mlx->_m.mapImg = mlx->img;
	mlx->_m.mapImgAddr = mlx->addr;
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
		if (mlx->_m.displayMap > 0)
		{
			if (x < mlx->_p.playerX + 100 && y < mlx->_p.playerY + 100)
				my_mlx_pixel_put(mlx, x, y, RAYCOLOR);
		}
		else
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
}

void	transparent_Bg(t_mlx *mlx, int img_width, int img_height)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
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
			my_mlx_pixel_put(&tmp, x, y + i, shader(0x00a1a4a3, wallHeight * 400
						/ screenHeight));
			i++;
		}
		x++;
	}
	mlx_put_image_to_window(mlx->p_mlx, mlx->win, tmp.img, 0, 0);
	mlx_destroy_image(mlx->p_mlx, tmp.img);
}

void minimap(t_mlx *mlx)
{
	int x;
	int y;
	int minix = 0;
	int miniy = 0;
	int maxX;
	int maxY;

	x = (mlx->_p.playerX / mlx->_m.mapScale) - 4;
	// if (x < 0)
	// 	x = 0;	
	y = (mlx->_p.playerY / mlx->_m.mapScale) - 4;
	// if(y < 0)
	// 	y = 0;
	maxX = (mlx->_p.playerX / mlx->_m.mapScale) + 4;
	// if(maxX > mlx->_m.mapWidth)
	// 	maxX = mlx->_m.mapWidth;
	maxY = (mlx->_p.playerY / mlx->_m.mapScale) + 4;
	// if(maxY > mlx->_m.mapHeight)
	// 	maxY = mlx->_m.mapHeight;
	int	i;
	int	j;

	mlx->img = mlx_new_image(mlx->p_mlx, 9 * mlx->_m.mapScale,
			9 * mlx->_m.mapScale);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel,
			&mlx->line_length, &mlx->endian);
	transparent_Bg(mlx, 9 * mlx->_m.mapScale, 9 * mlx->_m.mapScale);
	while (y < maxY)
	{
		x = (mlx->_p.playerX / mlx->_m.mapScale) - 4;
		if (y < 0)
		{
			y++;
			miniy++;
			continue;
		}
		if (y >= mlx->_m.mapHeight)
			break;
		// if (x < 0)
		// 	x = 0;	
		minix = 0;
		while (x < maxX)
		{
			if(x < 0)
			{
				x++;
				minix++;
				continue;
			}
			if (x >= mlx->_m.mapWidth)
				break;
			// we set block dementions
			i = miniy * mlx->_m.mapScale;
			j = minix * mlx->_m.mapScale;
			// we draw the block
			while (i < (miniy + 1) * mlx->_m.mapScale)
			{
				while (j < (minix + 1) * mlx->_m.mapScale)
				{

					if (mlx->_m.map[y][x] != '1')
					{
						// add edges to map
						if ((i + 1 == (y + 1) * mlx->_m.mapScale && (y + 1 < mlx->_m.mapHeight && mlx->_m.map[y + 1][x] == '1')) ||
							(j + 1 == (x + 1) * mlx->_m.mapScale && (x + 1 < mlx->_m.mapWidth && mlx->_m.map[y][x + 1] == '1')))
							my_mlx_pixel_put(mlx, j, i, WHITE);
						else
						my_mlx_pixel_put(mlx, j, i , FLOORCOLOR);
					}
					// draw the floor
					else
					{
						// add edges to map
						if ((i + 1 == (y + 1) * mlx->_m.mapScale && (y + 1 < mlx->_m.mapHeight && mlx->_m.map[y + 1][x] != '1')) ||
							(j + 1 == (x + 1) * mlx->_m.mapScale && (x + 1 < mlx->_m.mapWidth && mlx->_m.map[y][x + 1] != '1')))
							my_mlx_pixel_put(mlx, j, i, WHITE);
						else
							my_mlx_pixel_put(mlx, j, i , WALLCOLOR);
						// draw the wall
					}
					j++;
				}
				// we reset the x axis
				j = minix * mlx->_m.mapScale;
				i++;
			}
			x++;
			minix++;
		}
		y++;
		miniy++;
	}
	// draw the player dot
	i = - 5;
	while (i < 5)
	{
		j = - 5;
		while(j < 5)
		{
			my_mlx_pixel_put(mlx,(9 * mlx->_m.mapScale / 2) + j,(9 * mlx->_m.mapScale / 2) + i, 0x00FF0000);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(mlx->p_mlx, mlx->win, mlx->img, 25, 25);
	mlx_destroy_image(mlx->p_mlx, mlx->img);
}
