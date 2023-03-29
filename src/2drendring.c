/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2drendring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 22:59:47 by del-khay          #+#    #+#             */
/*   Updated: 2023/03/29 20:23:02 by del-khay         ###   ########.fr       */
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
		x = (screenWidth / 2) - (mlx->_m.mapWidth * mlx->_m.mapScale / 2)
			+ mlx->_p.playerX - player_thickness / 2;
		y = (screenHeight / 2) - (mlx->_m.mapHeight * mlx->_m.mapScale / 2)
			+ mlx->_p.playerY - player_thickness / 2;
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
						if ((i + 1 == (y + 1) * mlx->_m.mapScale && (y
									+ 1 < mlx->_m.mapHeight && mlx->_m.map[y
									+ 1][x] == '1')) ||
							(j + 1 == (x + 1) * mlx->_m.mapScale && (x
										+ 1 < mlx->_m.mapWidth
										&& mlx->_m.map[y][x + 1] == '1')))
							my_mlx_pixel_put(mlx, j, i, WHITE);
						else
							my_mlx_pixel_put(mlx, j, i, FLOORCOLOR);
					}
					// draw the floor
					else
					{
						// add edges to map
						if ((i + 1 == (y + 1) * mlx->_m.mapScale && (y
									+ 1 < mlx->_m.mapHeight && mlx->_m.map[y
									+ 1][x] != '1')) ||
							(j + 1 == (x + 1) * mlx->_m.mapScale && (x
										+ 1 < mlx->_m.mapWidth
										&& mlx->_m.map[y][x + 1] != '1')))
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

float	cast(t_ray *ray, t_mlx *mlx)
{
	int		x;
	int		y;
	int		i;
	float	distanceToWall;
	float	rayAngle;

	rayAngle = ray->startAngle;
	i = 0;
	x = floor((cos(rayAngle) * i) + ((mlx->_p.playerX / mlx->_m.mapScale)
				* ray->ScaleFactor));
	y = floor((sin(rayAngle) * i) + ((mlx->_p.playerY / mlx->_m.mapScale)
				* ray->ScaleFactor));
	// cast the ray
	while (1)
	{
		if (mlx->_m.displayMap > 0)
		{
			if ((x / ray->ScaleFactor) * mlx->_m.mapScale < mlx->_p.playerX
				+ 100 && (y / ray->ScaleFactor)
				* mlx->_m.mapScale < mlx->_p.playerY + 100)
				my_mlx_pixel_put(mlx, (x / ray->ScaleFactor) * mlx->_m.mapScale,
						(y / ray->ScaleFactor) * mlx->_m.mapScale, RAYCOLOR);
		}
		else
			my_mlx_pixel_put(mlx, (x / ray->ScaleFactor) * mlx->_m.mapScale, (y / ray->ScaleFactor) * mlx->_m.mapScale, RAYCOLOR);
		x = floor(cos(rayAngle) * i) + (((mlx->_p.playerX / mlx->_m.mapScale)
					* ray->ScaleFactor));
		if (mlx->_m.map[y / SCALEFACTOR][x / SCALEFACTOR] == '1')
		{
			// y = floor((sin(rayAngle) * i) + mlx->_p.playerY);
			ray->hitSide = VERTICAL;
			break ;
		}
		y = floor((sin(rayAngle) * i) + ((mlx->_p.playerY / mlx->_m.mapScale)
					* ray->ScaleFactor));
		if (mlx->_m.map[y / SCALEFACTOR][x / SCALEFACTOR] == '1')
		{
			ray->hitSide = HORIZONTAL;
			break ;
		}
		i++;
	}
	// save the hit point
	ray->hitPoint[X] = (x / ray->ScaleFactor) * mlx->_m.mapScale;
	ray->hitPoint[Y] = (y / ray->ScaleFactor) * mlx->_m.mapScale;
	// calculate the distance and return it
	distanceToWall = sqrt(pow(x - ((mlx->_p.playerX / mlx->_m.mapScale)
					* ray->ScaleFactor), 2) + pow(y - ((mlx->_p.playerY
						/ mlx->_m.mapScale) * ray->ScaleFactor), 2));
	// correct the distance
	distanceToWall *= cos(mlx->_p.playerAngle - rayAngle);
	return (distanceToWall);
}
void	initRay(t_ray *ray, t_mlx *mlx)
{
	ray->startAngle = mlx->_p.playerAngle - (FOV / 2);
	ray->endAngle = mlx->_p.playerAngle + (FOV / 2);
	ray->rayNumber = RAYNUMBER;
	ray->ScaleFactor = SCALEFACTOR;
	ray->step = FOV / ray->rayNumber;
}

int	getColor(t_ray *ray, t_mlx *mlx)
{
	int	color;

	color = 0;
	if (ray->hitPoint[Y] - mlx->_p.playerY < 0 && ray->hitSide == HORIZONTAL)
		color = 0x00555652; // green for north
	if (ray->hitPoint[Y] - mlx->_p.playerY >= 0 && ray->hitSide == HORIZONTAL)
		color = METAL; // red for south
	if (ray->hitPoint[X] - mlx->_p.playerX < 0 && ray->hitSide == VERTICAL)
		color = shader(WHITE, 50); // blue for east
	if (ray->hitPoint[X] - mlx->_p.playerX >= 0 && ray->hitSide == VERTICAL)
		color = shader(0x00505652, 40); // yellow for west
	return (color);
}

void	rayCaster(t_mlx *mlx)
{
	t_ray	ray;
	int		i;

	initRay(&ray, mlx);
	i = 0;
	while (i < ray.rayNumber)
	{
		mlx->distances[i] = cast(&ray, mlx);
		mlx->rayColor[i] = getColor(&ray, mlx);
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
	tmp.img = mlx_new_image(mlx->p_mlx, screenWidth, screenHeight);
	tmp.addr = mlx_get_data_addr(tmp.img, &tmp.bits_per_pixel, &tmp.line_length,
			&mlx->endian);
	// fill the screen column by column
	while (x < screenWidth)
	{
		// calculate the wall height
		wallHeight = (SCALEFACTOR / mlx->distances[x]) * SCREEN_DIST;
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
		// draw the floor
		i += wallHeight;
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
			my_mlx_pixel_put(&tmp, x, y + i, shader(METAL, wallHeight * 400
						/ screenHeight));
			i++;
		}
		x++;
	}
	mlx_put_image_to_window(mlx->p_mlx, mlx->win, tmp.img, 0, 0);
	mlx_destroy_image(mlx->p_mlx, tmp.img);
}
