/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 00:21:11 by del-khay          #+#    #+#             */
/*   Updated: 2023/04/10 20:45:16 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

void	init_map(t_mlx *mlx, t_components *comp)
{
	mlx->_m.map = comp->map;
	if (mlx->_m.map == NULL)
	{
		printf("Error reading map \n");
		exit(0);
	}
	mlx->_m.map_width = comp->map_w;
	mlx->_m.map_height = comp->map_h;
	mlx->_m.map_scale = min(SCREEN_WIDTH / mlx->_m.map_width, SCREEN_HEIGHT
			/ mlx->_m.map_height);
	if (mlx->_m.map_scale < 0)
	{
		printf("Error map is too big \n");
		exit(0);
	}
	mlx->_m.display_map = 1;
	mlx->_m.img_xpos = 100 - mlx->_p.player_x;
	mlx->_m.img_ypos = 100 - mlx->_p.player_y;
	mlx->_m.c_color = comp->elements.c_color;
	mlx->_m.f_color = comp->elements.f_color;
}

void	init_player_img(t_mlx *mlx)
{
	int	i;
	int	j;

	mlx->_p.icon_img = mlx_xpm_file_to_image(mlx->p_mlx, "./testxpm/player.xpm",
			&i, &j);
	mlx->sp_ptr = calloc(1, sizeof(t_data));
	if (mlx->_p.icon_img == NULL)
	{
		printf("Error reading player icon \n");
		exit(0);
	}
}

void	init_player(t_mlx *mlx, t_components *comp)
{
	mlx->_p.player_x = comp->player_x * mlx->_m.map_scale;
	mlx->_p.player_y = comp->player_y * mlx->_m.map_scale;
	mlx->_p.player_x += mlx->_m.map_scale / 2;
	mlx->_p.player_y += mlx->_m.map_scale / 2;
	if (mlx->_m.map[comp->player_y][comp->player_x] == 'N')
		mlx->_p.player_angle = 3 * M_PI / 2;
	else if (mlx->_m.map[comp->player_y][comp->player_x] == 'S')
		mlx->_p.player_angle = M_PI / 2;
	else if (mlx->_m.map[comp->player_y][comp->player_x] == 'E')
		mlx->_p.player_angle = 0;
	else if (mlx->_m.map[comp->player_y][comp->player_x] == 'W')
		mlx->_p.player_angle = M_PI;
	else
	{
		printf("Error reading player position \n");
		exit(0);
	}
	mlx->_p.pmovment_speed = 4;
	mlx->_p.rotation_speed = 6 * (M_PI / 180);
	init_player_img(mlx);
	init_sprite(mlx);
}

void	init_data(t_mlx *mlx, t_components *comp)
{
	int	i;

	i = 0;
	mlx->on_change = 0;
	mlx->shoot = 0;
	init_texture(mlx, comp);
	init_map(mlx, comp);
	init_player(mlx, comp);
	init_loadscreen(mlx);
	init_gun(mlx);
	mlx->distances = malloc(sizeof(float) * RAYNUMBER);
	mlx->_d = calloc(RAYNUMBER, sizeof(t_door));
	mlx->_sp = calloc(RAYNUMBER, sizeof(t_sprite));
	mlx->fov = 60 * (M_PI / 180);
	mlx->sreen_dist = (SCREEN_WIDTH / 2) / tan(mlx->fov / 2);
	mlx->mouse = 0;
	mlx->_mo.mouse_x = SCREEN_WIDTH / 2;
	mlx->_mo.mouse_y = SCREEN_HEIGHT / 2;
	mlx->_mo.mouse_angle = 0;
	mlx->_mo.y_offset = 0;
	while (i < 8)
	{
		mlx->control_keys[i] = RELEASED;
		i++;
	}
}
