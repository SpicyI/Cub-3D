/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 02:10:23 by del-khay          #+#    #+#             */
/*   Updated: 2023/04/08 02:10:25 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../Cub3D.h"

void	crop_img(t_mlx *mlx, int x, int y)
{
	int	reset_y;

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

void	transparent_bg(t_mlx *mlx, int img_width, int img_height)
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
