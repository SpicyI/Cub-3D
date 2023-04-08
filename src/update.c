/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 01:28:22 by del-khay          #+#    #+#             */
/*   Updated: 2023/04/08 01:31:59 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

void	arrows(t_mlx *mlx, float step_x, float step_y)
{
	if (mlx->control_keys[LEFT_ARROW] == PRESSED)
	{
		mlx->_p.player_angle -= mlx->_p.rotation_speed;
	}
	if (mlx->control_keys[DOWN_ARROW] == PRESSED
		|| mlx->control_keys[S_KEY] == PRESSED)
		move_down(mlx, step_x, step_y);
	if (mlx->control_keys[RIGHT_ARROW] == PRESSED)
	{
		mlx->_p.player_angle += mlx->_p.rotation_speed;
	}
	if (mlx->control_keys[UP_ARROW] == PRESSED
		|| mlx->control_keys[W_KEY] == PRESSED)
		move_up(mlx, step_x, step_y);
}

void	open_door(t_mlx *mlx)
{
	int		x;
	int		y;
	int		i;

	i = 0;
	while (i < 50)
	{
		x = (cos(mlx->_p.player_angle) * i) + mlx->_p.player_x;
		y = (sin(mlx->_p.player_angle) * i) + mlx->_p.player_y;
		if (mlx->_m.map[y / mlx->_m.map_scale][x / mlx->_m.map_scale] == 'D')
		{
			mlx->_m.map[y / mlx->_m.map_scale][x / mlx->_m.map_scale] = 'O';
			break ;
		}
		else if (mlx->_m.map[y / mlx->_m.map_scale][x
			/ mlx->_m.map_scale] == 'O')
		{
			if (mlx->_m.map[(int)mlx->_p.player_y
					/ mlx->_m.map_scale][(int)mlx->_p.player_y
				/ mlx->_m.map_scale] != 'O')
				mlx->_m.map[y / mlx->_m.map_scale][x / mlx->_m.map_scale] = 'D';
			break ;
		}
		i++;
	}
}

void	update_minimap(t_mlx *mlx)
{
	if (mlx->_m.display_map > 0)
	{
		mlx->_m.img_xpos = (100 - mlx->_p.player_x);
		mlx->_m.img_ypos = (100 - mlx->_p.player_y);
	}
	else
	{
		mlx->_m.img_xpos = (SCREEN_WIDTH - mlx->_m.map_width
				* mlx->_m.map_scale) / 2;
		mlx->_m.img_ypos = (SCREEN_HEIGHT - mlx->_m.map_height
				* mlx->_m.map_scale) / 2;
	}
}

void	update(t_mlx *mlx)
{
	float	step_x;
	float	step_y;

	step_x = (cos(mlx->_p.player_angle) * mlx->_p.pmovment_speed);
	step_y = (sin(mlx->_p.player_angle) * mlx->_p.pmovment_speed);
	if (mlx->mouse == 1)
	{
		mlx->_p.player_angle += mlx->_mo.mouse_angle;
	}
	else if (mlx->mouse == -1)
	{
		mlx->_p.player_angle -= mlx->_mo.mouse_angle;
	}
	arrows(mlx, step_x, step_y);
	key_stroke(mlx, step_x, step_y);
	update_minimap(mlx);
}
