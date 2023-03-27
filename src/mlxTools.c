/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxTools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 23:00:35 by del-khay          #+#    #+#             */
/*   Updated: 2023/03/27 20:30:08 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

void	my_mlx_pixel_put(t_mlx *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	exit_game(t_mlx *mlx)
{
	mlx_destroy_window(mlx->p_mlx, mlx->win);
	mlx_destroy_window(mlx->p_mlx, mlx->win2d);
	free(mlx->_m.map);
	exit(0);
}

int	render(t_mlx *mlx)
{
	mlx_clear_window(mlx->p_mlx, mlx->win);
	mlx_put_image_to_window(mlx->p_mlx, mlx->win, mlx->_m.mapImg, (screenWidth
				/ 2) - (mlx->_m.mapWidth * mlx->_m.mapScale / 2), (screenHeight
				/ 2) - (mlx->_m.mapHeight * mlx->_m.mapScale / 2));
	putPlayer(mlx);
	putDirection(mlx);
	rayCaster(mlx);
	if (mlx->_m.displayMap > 0)
	{
		mlx_clear_window(mlx->p_mlx, mlx->win);
	}
	putWalls(mlx);
	return (0);
}