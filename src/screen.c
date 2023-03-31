/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 04:50:54 by del-khay          #+#    #+#             */
/*   Updated: 2023/03/31 04:18:20 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Cub3D.h"

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
		wallHeight = (mlx->_m.map_scale / mlx->distances[x]) * mlx->sreen_dist;
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
			my_mlx_pixel_put(&tmp, x, y + i, shader(METAL, wallHeight * 400
						/ SCREEN_HEIGHT));
			i++;
		}
		x++;
	}
	mlx_put_image_to_window(mlx->p_mlx, mlx->win, tmp.img, 0, 0);
	mlx_destroy_image(mlx->p_mlx, tmp.img);
}