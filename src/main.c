/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 23:00:10 by del-khay          #+#    #+#             */
/*   Updated: 2023/03/30 04:43:39 by del-khay         ###   ########.fr       */
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
	mlx->ray_color = malloc(sizeof(int) * RAYNUMBER);
	mlx->_m.map = comp->map;
	mlx->_e = comp->elements;
	mlx->_m.map_width = 24;
	mlx->_m.map_height = 24 + 5;
	mlx->_m.map_scale = min(SCREEN_WIDTH / mlx->_m.map_width, SCREEN_HEIGHT
			/ mlx->_m.map_height);
	mlx->_p.player_x = (11 * mlx->_m.map_scale);
	mlx->_p.player_y = (11 * mlx->_m.map_scale);
	mlx->_p.player_angle = M_PI / 2;
	mlx->_p.pmovment_speed = 6;
	mlx->_p.rotation_speed = 4 * (M_PI / 180);
	mlx->_m.display_map = 1;
	mlx->_m.img_xpos = 100 - mlx->_p.player_x;
	mlx->_m.img_ypos = 100 - mlx->_p.player_y;
	mlx->on_change = 0;
	mlx->fov = 60 * (M_PI / 180);
	mlx->sreen_dist = (SCREEN_WIDTH / 2) / tan(mlx->fov / 2);
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
	mlx_loop(mlx.p_mlx);
}
