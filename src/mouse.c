/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 22:21:26 by del-khay          #+#    #+#             */
/*   Updated: 2023/04/09 21:46:29 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

int	mouse_click(int button, int x, int y, t_mlx *mlx)
{
	(void)x;
	(void)y;
	if (button == 1)
	{
		if (mlx->shoot == 0)
			mlx->shoot = 1;
	}
	return (0);
}

int	mouse_controls(int x, int y, t_mlx *mlx)
{
	int	mouse_step;

	mlx_mouse_hide();
	if (x != mlx->_mo.mouse_x || y != mlx->_mo.mouse_y)
	{
		mlx->_mo.y_offset = ((y - (SCREEN_HEIGHT / 2)) * -1);
		mouse_step = x - mlx->_mo.mouse_x;
		mlx->_mo.mouse_angle = atan(abs(mouse_step / 2) / mlx->sreen_dist);
		if (mouse_step < 0)
			mlx->mouse = -1;
		else if (mouse_step >= 0)
			mlx->mouse = 1;
		mlx->_mo.mouse_x = x;
		if (mlx->_mo.mouse_x > SCREEN_WIDTH || mlx->_mo.mouse_x < 0)
		{
			mlx->_mo.mouse_x = SCREEN_WIDTH / 2;
			mlx_mouse_move(mlx->win, SCREEN_WIDTH / 2, y);
		}
		if (y > SCREEN_HEIGHT + 100)
			mlx_mouse_move(mlx->win, mlx->_mo.mouse_x, SCREEN_HEIGHT);
		else if (y < 0 - 100)
			mlx_mouse_move(mlx->win, mlx->_mo.mouse_x, 0);
		mlx->_mo.mouse_y = y;
	}
	return (0);
}
