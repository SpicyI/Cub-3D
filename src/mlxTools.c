/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxTools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 23:00:35 by del-khay          #+#    #+#             */
/*   Updated: 2023/03/24 21:27:17 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

void	my_mlx_pixel_put(t_mlx *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	exit_game(t_mlx *mlx)
{
	mlx_destroy_window(mlx->p_mlx, mlx->win);
	mlx_destroy_window(mlx->p_mlx, mlx->win2d);
	exit(0);
}

int render(t_mlx * mlx)
{
	// Draw the map
    mlx_put_image_to_window(mlx->p_mlx, mlx->win2d, mlx->_m.mapImg, 0, 0);
    mlx_put_image_to_window(mlx->p_mlx, mlx->win, mlx->_m.mapImg, 0, 0);
	putPlayer(mlx);
	putDirection(mlx);
    return(0);
}