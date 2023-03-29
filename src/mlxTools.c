/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxTools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 23:00:35 by del-khay          #+#    #+#             */
/*   Updated: 2023/03/29 02:40:26 by del-khay         ###   ########.fr       */
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
	if (!mlx->inChange)
		return 1;
	mlx_clear_window(mlx->p_mlx, mlx->win);
	drawMap(mlx);
	mlx->img = mlx_new_image(mlx->p_mlx, mlx->_m.mapWidth * mlx->_m.mapScale,
			mlx->_m.mapHeight * mlx->_m.mapScale);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel,
			&mlx->line_length, &mlx->endian);
	// draw the transparent background
	transparent_Bg(mlx,mlx->_m.mapWidth * mlx->_m.mapScale,mlx->_m.mapHeight * mlx->_m.mapScale);
	rayCaster(mlx);
	mlx->_p.playerImg = mlx->img;
	putWalls(mlx);
	
	if (mlx->_m.displayMap  > 0)
	{
		mlx_put_image_to_window(mlx->p_mlx, mlx->win, mlx->_m.mapImg,(100 - mlx->_p.playerX) ,(100 - mlx->_p.playerY) );
		mlx_put_image_to_window(mlx->p_mlx, mlx->win, mlx->_p.playerImg,(100 - mlx->_p.playerX) ,(100 - mlx->_p.playerY) );
	}
	else
	{
		mlx_put_image_to_window(mlx->p_mlx, mlx->win, mlx->_m.mapImg, (screenWidth
					/ 2) - (mlx->_m.mapWidth * mlx->_m.mapScale / 2), (screenHeight
					/ 2) - (mlx->_m.mapHeight * mlx->_m.mapScale / 2));
		mlx_put_image_to_window(mlx->p_mlx, mlx->win, mlx->_p.playerImg, (screenWidth / 2)
			- (mlx->_m.mapWidth * mlx->_m.mapScale / 2), (screenHeight / 2)
			- (mlx->_m.mapHeight * mlx->_m.mapScale / 2));
	}
	mlx_destroy_image(mlx->p_mlx, mlx->_m.mapImg);
	putPlayer(mlx);
	// else
	// 	minimap(mlx);
	mlx_destroy_image(mlx->p_mlx, mlx->_p.playerImg);
	mlx->inChange = 0;
	return (0);
}