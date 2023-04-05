/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 23:00:54 by del-khay          #+#    #+#             */
/*   Updated: 2023/04/05 19:49:22 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

int	keys_pressed(int key, t_mlx *mlx)
{
	mlx->on_change = 1;
	if (!mlx->img)
		return (0);
	if (key == 53)
		exit_game(mlx);
	if (key == 48)
		mlx->_m.display_map *= -1;
	if (key == 123)
		mlx->control_keys[LEFT_ARROW] = PRESSED;
	if (key == 124)
		mlx->control_keys[RIGHT_ARROW] = PRESSED;
	if (key == 125)
		mlx->control_keys[DOWN_ARROW] = PRESSED;
	if (key == 126)
		mlx->control_keys[UP_ARROW] = PRESSED;
	if (key == 13)
		mlx->control_keys[W_KEY] = PRESSED;
	if (key == 0)
		mlx->control_keys[A_KEY] = PRESSED;
	if (key == 1)
		mlx->control_keys[S_KEY] = PRESSED;
	if (key == 2)
		mlx->control_keys[D_KEY] = PRESSED;
	return (0);
}

void	move_up(t_mlx *mlx, float step_x, float step_y)
{
	int	player_x;
	int	player_y;
	int	jump_posx;
	int	jump_posy;

	player_x = mlx->_p.player_x / mlx->_m.map_scale;
	player_y = mlx->_p.player_y / mlx->_m.map_scale;
	jump_posx = (mlx->_p.player_x + step_x) / mlx->_m.map_scale;
	jump_posy = (mlx->_p.player_y + step_y) / mlx->_m.map_scale;
	if (mlx->_m.map[player_y][jump_posx] != '1')
		mlx->_p.player_x += step_x;
	if (mlx->_m.map[jump_posy][player_x] != '1')
		mlx->_p.player_y += step_y;
}

void	move_down(t_mlx *mlx, float step_x, float step_y)
{
	int	player_x;
	int	player_y;
	int	jump_posx;
	int	jump_posy;

	player_x = mlx->_p.player_x / mlx->_m.map_scale;
	player_y = mlx->_p.player_y / mlx->_m.map_scale;
	jump_posx = (mlx->_p.player_x - step_x) / mlx->_m.map_scale;
	jump_posy = (mlx->_p.player_y - step_y) / mlx->_m.map_scale;

	if (mlx->_m.map[player_y][jump_posx] != '1')
		mlx->_p.player_x -= step_x;
	if (mlx->_m.map[jump_posy][player_x] != '1')
		mlx->_p.player_y -= step_y;
}

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

void	key_stroke(t_mlx *mlx, float step_x, float step_y)
{
	if (mlx->control_keys[A_KEY] == PRESSED)
	{
		step_x = cos(mlx->_p.player_angle + (M_PI / 2))
			* mlx->_p.pmovment_speed;
		step_y = sin(mlx->_p.player_angle + (M_PI / 2))
			* mlx->_p.pmovment_speed;
		move_down(mlx, step_x, step_y);
	}
	if (mlx->control_keys[D_KEY] == PRESSED)
	{
		step_x = cos(mlx->_p.player_angle + (M_PI / 2))
			* mlx->_p.pmovment_speed;
		step_y = sin(mlx->_p.player_angle + (M_PI / 2))
			* mlx->_p.pmovment_speed;
		move_up(mlx, step_x, step_y);
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

int	plane_controls2(int key, t_mlx *mlx)
{
	if (key == 123)
		mlx->control_keys[LEFT_ARROW] = RELEASED;
	if (key == 124)
		mlx->control_keys[RIGHT_ARROW] = RELEASED;
	if (key == 125)
		mlx->control_keys[DOWN_ARROW] = RELEASED;
	if (key == 126)
		mlx->control_keys[UP_ARROW] = RELEASED;
	if (key == 13)
		mlx->control_keys[W_KEY] = RELEASED;
	if (key == 0)
		mlx->control_keys[A_KEY] = RELEASED;
	if (key == 1)
		mlx->control_keys[S_KEY] = RELEASED;
	if (key == 2)
		mlx->control_keys[D_KEY] = RELEASED;
	return (0);
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
