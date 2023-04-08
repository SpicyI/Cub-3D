/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 05:03:54 by del-khay          #+#    #+#             */
/*   Updated: 2023/04/08 05:05:15 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

void	put_player(t_mlx *mlx)
{
	int	y;
	int	player_thickness;
	int	x;

	x = 0;
	y = 0;
	player_thickness = 30;
	x = (mlx->_m.img_xpos + mlx->_p.player_x) - player_thickness / 2;
	y = (mlx->_m.img_ypos + +mlx->_p.player_y) - player_thickness / 2;
	mlx_put_image_to_window(mlx->p_mlx, mlx->win, mlx->_p.icon_img, x, y);
}
