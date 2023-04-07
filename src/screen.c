/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 04:50:54 by del-khay          #+#    #+#             */
/*   Updated: 2023/04/07 06:50:24 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Cub3D.h"

// int shader(int color, int shade_percentage)
// {
//     // Extract the red, green, and blue components of the input color.
//     unsigned char red = (color >> 16) & 0xFF;
//     unsigned char green = (color >> 8) & 0xFF;
//     unsigned char blue = color & 0xFF;

// 	if (shade_percentage < 0)
// 		shade_percentage *= -1;
//     // Apply the shade percentage to each color component.
// 	if (shade_percentage > 100)
// 		shade_percentage = 100;
//     red = (unsigned char)(red * shade_percentage / 100);
//     green = (unsigned char)(green * shade_percentage / 100);
//     blue = (unsigned char)(blue * shade_percentage / 100);

//     // Ensure that the modified color components are within the valid range of 0 to 255.
//     red = (red > 255) ? 255 : red;
//     green = (green > 255) ? 255 : green;
//     blue = (blue > 255) ? 255 : blue;

//     // Combine the modified color components into a single integer and return it.
//     return (red << 16) | (green << 8) | blue;
// }
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
	int 	offset;
	int 	color;
	t_mlx	tmp;

	x = 0;
	y = 0;
	i = 0;
	tmp.img = mlx_new_image(mlx->p_mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	tmp.addr = mlx_get_data_addr(tmp.img, &tmp.bits_per_pixel, &tmp.line_length,
			&mlx->endian);
	offset = (SCREEN_HEIGHT / 2) + mlx->_mo.y_offset;
	// fill the screen column by column
	while (x < SCREEN_WIDTH)
	{
		// calculate the wall height
		wallHeight = (mlx->_m.map_scale / mlx->distances[x]) * mlx->sreen_dist;
		// offset the middle of the screen
		y = offset - (wallHeight / 2);
		if(y > SCREEN_HEIGHT)
			y = SCREEN_HEIGHT;
		// draw the wall strip
		i = 0 - y;
		while (i < wallHeight && y + i < SCREEN_HEIGHT)
		{
			if (y + i < 0)
			{
				i++;
				continue;
			}
			color = get_img_color(&(mlx->_t[mlx->_s[x].tex]), mlx->_s[x].x, i * mlx->_t[mlx->_s[x].tex].height / wallHeight);
			my_mlx_pixel_put(&tmp, x, y + i, shader(color, wallHeight * 400
						/ SCREEN_HEIGHT));
			i++;
		}
		while (y + i < SCREEN_HEIGHT)
		{
			if (y + i < 0)
			{
				i++;
				continue;
			}
			my_mlx_pixel_put(&tmp, x, y + i, shader(GROUNDCOLOR, (i) * 100 / (SCREEN_HEIGHT/ 2)));
			i++;
		}
		i = 0;
		// draw the ceiling
		while (i < y && i < SCREEN_HEIGHT)
		{
			my_mlx_pixel_put(&tmp, x, i, shader(SKYCOLOR, 100 - ((i / y) * 100)));
			i++;
		}
		x++;
	}
	mlx_put_image_to_window(mlx->p_mlx, mlx->win, tmp.img, 0, 0);
	mlx_destroy_image(mlx->p_mlx, tmp.img);
	tmp.img = mlx_new_image(mlx->p_mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	tmp.addr = mlx_get_data_addr(tmp.img, &tmp.bits_per_pixel, &tmp.line_length,
			&mlx->endian);
	transparent_Bg(&tmp, SCREEN_WIDTH, SCREEN_HEIGHT);
	x = 0;
	y = 0;
	int door_height;
	while (x < SCREEN_WIDTH)
	{
		
		if (mlx->_d[x].door_exist)
		{
			door_height = (mlx->_m.map_scale / mlx->_d[x].door_dist) * mlx->sreen_dist;
			y = offset - (door_height / 2);
			if(y > SCREEN_HEIGHT)
				y = SCREEN_HEIGHT;
			i = 0;
			if (y + i < 0)
				i = 0 - y;
			while (i < door_height && y + i < SCREEN_HEIGHT)
			{
				if (y + i < 0)
				{
					i++;
					continue;
				}
				if (i < (door_height * 0.05))
					my_mlx_pixel_put(&tmp, x, y + i, METAL);
				else
				my_mlx_pixel_put(&tmp, x, y + i, mlx->_d[x].door_color);
				i++;
			}
		}
		x++;
	}
	mlx_put_image_to_window(mlx->p_mlx, mlx->win, tmp.img, 0, 0);
	mlx_destroy_image(mlx->p_mlx, tmp.img);

	
	// mlx->_mo.y_offset = 0;
}