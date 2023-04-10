/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 23:00:10 by del-khay          #+#    #+#             */
/*   Updated: 2023/04/10 20:47:07 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

int	min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

t_inter	rmin(t_inter r1, t_inter r2)
{
	if (r1.door_dest < r2.door_dest)
		return (r1);
	return (r2);
}

t_inter	smin(t_inter r1, t_inter r2)
{
	if (r1.sprite_dist < r2.sprite_dist)
	{
		r1.hit_side = VERTICAL;
		return (r1);
	}
	r2.hit_side = HORIZONTAL;
	return (r2);
}

int	main(int argc, char **argv)
{
	t_mlx			mlx;
	t_components	comp;
	pthread_t		gun_thread;

	if (argc != 2)
		return (printf(YEL "Usage: ./cub3d map.cub \n" RESET));
	initialize_comps(&comp);
	if (!read_file(argv[1], &comp) || !check_comps(&comp))
		return (0);
	set_player_cords(&comp);
	mlx.p_mlx = mlx_init();
	mlx.ident = 0;
	init_data(&mlx, &comp);
	pthread_create(&mlx.thread, NULL, &framer, &mlx);
	pthread_create(&gun_thread, NULL, &gun_framer, &mlx);
	mlx.win = mlx_new_window(mlx.p_mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D");
	mlx_hook(mlx.win, 17, 0, (int (*)()) & exit_game, &mlx);
	mlx_loop_hook(mlx.p_mlx, &render, &mlx);
	mlx_hook(mlx.win, 2, 0, &keys_pressed, &mlx);
	mlx_hook(mlx.win, 3, 0, &key_released, &mlx);
	mlx_hook(mlx.win, 6, 0, &mouse_controls, &mlx);
	mlx_hook(mlx.win, 5, 0, &mouse_click, &mlx);
	mlx_loop(mlx.p_mlx);
}
