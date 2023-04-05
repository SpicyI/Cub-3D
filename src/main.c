/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 23:00:10 by del-khay          #+#    #+#             */
/*   Updated: 2023/04/05 19:50:17 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

int	min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

void	init_data(t_mlx *mlx, t_components *comp)
{
	mlx->distances = malloc(sizeof(float) * RAYNUMBER);
	mlx->_t = malloc(sizeof(t_data) * 4);
	// ! the array to pass hit_side and the x pos for the texture
	mlx->_s = malloc(sizeof(t_side) * RAYNUMBER);
	mlx->_m.map = comp->map;
	mlx->_e = comp->elements;
	mlx->_m.map_width = 24;
	mlx->_m.map_height = 24 + 5;
	mlx->_m.map_scale = min(SCREEN_WIDTH / mlx->_m.map_width, SCREEN_HEIGHT
			/ mlx->_m.map_height);
	mlx->_p.player_x = (11 * mlx->_m.map_scale);
	mlx->_p.player_y = (11 * mlx->_m.map_scale);
	mlx->_p.player_angle = M_PI / 2;
	mlx->_p.pmovment_speed = 4;
	mlx->_p.rotation_speed = 6 * (M_PI / 180);
	mlx->_m.display_map = 1;
	mlx->_m.img_xpos = 100 - mlx->_p.player_x;
	mlx->_m.img_ypos = 100 - mlx->_p.player_y;
	mlx->on_change = 0;
	mlx->fov = 60 * (M_PI / 180);
	mlx->sreen_dist = (SCREEN_WIDTH / 2) / tan(mlx->fov / 2);
	mlx->mouse = 0;
	mlx->_mo.mouse_x = SCREEN_WIDTH / 2;
	mlx->_mo.mouse_y = SCREEN_HEIGHT / 2;
	mlx->_mo.mouse_angle = 0;
	mlx->_mo.y_offset = 0;
	int i = 0;
	while (i < 8)
	{
		mlx->control_keys[i] = RELEASED;
		i++;
	}
	// * init textures
	mlx->_t[NO].img = mlx_xpm_file_to_image(mlx->p_mlx, "./src/meme.xpm",
			&mlx->_t[NO].width, &mlx->_t[NO].height);
	mlx->_t[NO].addr = mlx_get_data_addr(mlx->_t[NO].img, &mlx->_t[NO].bits_per_pixel,
			&mlx->_t[NO].line_length, &mlx->_t[NO].endian);
			
	mlx->_t[SO].img = mlx_xpm_file_to_image(mlx->p_mlx, "./src/meme.xpm",
			&mlx->_t[SO].width, &mlx->_t[SO].height);
	mlx->_t[SO].addr = mlx_get_data_addr(mlx->_t[SO].img, &mlx->_t[SO].bits_per_pixel,
			&mlx->_t[SO].line_length, &mlx->_t[SO].endian);
	
	mlx->_t[WE].img = mlx_xpm_file_to_image(mlx->p_mlx, "./src/intro.xpm",
			&mlx->_t[WE].width, &mlx->_t[WE].height);
	mlx->_t[WE].addr = mlx_get_data_addr(mlx->_t[WE].img, &mlx->_t[WE].bits_per_pixel,
			&mlx->_t[WE].line_length, &mlx->_t[WE].endian);
			
	mlx->_t[EA].img = mlx_xpm_file_to_image(mlx->p_mlx, "./src/intro.xpm",
			&mlx->_t[EA].width, &mlx->_t[EA].height);
	mlx->_t[EA].addr = mlx_get_data_addr(mlx->_t[EA].img, &mlx->_t[EA].bits_per_pixel,
			&mlx->_t[EA].line_length, &mlx->_t[EA].endian);
}

void	put_intro(t_mlx *mlx)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	mlx->win = mlx_new_window(mlx->p_mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D");
	mlx->img = mlx_xpm_file_to_image(mlx->p_mlx, "./src/intro.xpm", &i, &j);
	mlx_put_image_to_window(mlx->p_mlx, mlx->win, mlx->img, 0, 0);
	mlx_destroy_image(mlx->p_mlx, mlx->img);
	mlx->_p.icon_img = mlx_xpm_file_to_image(mlx->p_mlx, "./src/player.xpm", &i,
			&j);
}

int mouse_controls(int x, int y, t_mlx *mlx)
{

	int mouse_step = 0;

	
	mlx_mouse_hide();
	if (x != mlx->_mo.mouse_x || y != mlx->_mo.mouse_y)
	{
		mlx->mouse = 1;
		// mlx->_mo.y_offset = ((y - (SCREEN_HEIGHT / 2)) * -1) / 2;
		mouse_step = x - mlx->_mo.mouse_x;
		mlx->_mo.mouse_angle = atan(abs(mouse_step / 2) / mlx->sreen_dist);
		if(mouse_step < 0)
			mlx->mouse = -1;
		else if (mouse_step >= 0)
			mlx->mouse = 1;
		mlx->_mo.mouse_x = x;
		if (mlx->_mo.mouse_x > SCREEN_WIDTH || mlx->_mo.mouse_x < 0)
		{
			mlx->_mo.mouse_x = SCREEN_WIDTH / 2;
			mlx_mouse_move(mlx->win, SCREEN_WIDTH / 2, y);
		}	
		// if (y > (SCREEN_HEIGHT / 2) + 100)
		// {
		// 	mlx->_mo.mouse_y = SCREEN_HEIGHT / 2;
		// 	mlx_mouse_move(mlx->win,mlx->_mo.mouse_x, (SCREEN_HEIGHT / 2) + 100);
		// }
		// else if (y < (SCREEN_HEIGHT / 2) - 100)
		// {
		// 	mlx->_mo.mouse_y = SCREEN_HEIGHT / 2;
		// 	mlx_mouse_move(mlx->win, mlx->_mo.mouse_x, (SCREEN_HEIGHT / 2) - 100);
		// // }
		// else
		// 	mlx->_mo.mouse_y = y;

	}
	return (0);
}


int	main(int argc, char **argv)
{
	t_mlx			mlx;
	t_components	comp;

	if (argc != 2)
		return (printf(YEL "Usage: ./cub3d map.cub \n" RESET));
	initialize_comps(&comp);
	if (!read_file(argv[1], &comp) || !check_comps(&comp))
		return (0);
	mlx.p_mlx = mlx_init();
	init_data(&mlx, &comp);
	put_intro(&mlx);
	mlx_hook(mlx.win, 17, 0, (int (*)()) & exit_game, &mlx);
	mlx_loop_hook(mlx.p_mlx, &render, &mlx);
	mlx_hook(mlx.win, 2, 0, &keys_pressed, &mlx);
	mlx_hook(mlx.win, 3, 0, &plane_controls2, &mlx);
	// mlx hook for mouse
	mlx_hook(mlx.win, 6, 0, &mouse_controls, &mlx);
	mlx_loop(mlx.p_mlx);
}
