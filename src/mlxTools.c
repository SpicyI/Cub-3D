/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxTools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 23:00:35 by del-khay          #+#    #+#             */
/*   Updated: 2023/03/30 02:08:01 by del-khay         ###   ########.fr       */
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
	free(mlx->_m.map);
	free(mlx->distances);
	free(mlx->ray_color);
	exit(0);
}

int	render(t_mlx *mlx)
{
	if (!mlx->on_change)
		return 1;
	update(mlx);
	mlx_clear_window(mlx->p_mlx, mlx->win);
	drawMap(mlx);
	mlx->img = mlx_new_image(mlx->p_mlx, mlx->_m.map_width * mlx->_m.map_scale,
			mlx->_m.map_height * mlx->_m.map_scale);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel,
			&mlx->line_length, &mlx->endian);
	transparent_Bg(mlx,mlx->_m.map_width * mlx->_m.map_scale,mlx->_m.map_height * mlx->_m.map_scale);
	rayCaster(mlx);
	mlx->_p.player_img = mlx->img;
	putWalls(mlx);
	mlx_put_image_to_window(mlx->p_mlx, mlx->win, mlx->_m.map_img,mlx->_m.img_xpos ,mlx->_m.img_ypos);
	mlx_destroy_image(mlx->p_mlx, mlx->_m.map_img);
	mlx_put_image_to_window(mlx->p_mlx, mlx->win, mlx->_p.player_img,mlx->_m.img_xpos,mlx->_m.img_ypos);
	putPlayer(mlx);
	mlx_destroy_image(mlx->p_mlx, mlx->_p.player_img);
	mlx->on_change = 0;
	return (0);
}