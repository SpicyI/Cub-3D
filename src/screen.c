/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 04:50:54 by del-khay          #+#    #+#             */
/*   Updated: 2023/04/10 02:40:54 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

void	draw_scene(t_mlx *mlx)
{
	t_scene	s;
	int		i;
	int		offset;

	s.x = 0;
	s.y = 0;
	i = 0;
	s.tmp.img = mlx_new_image(mlx->p_mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	s.tmp.addr = mlx_get_data_addr(s.tmp.img, &s.tmp.bits_per_pixel,
			&s.tmp.line_length, &mlx->endian);
	offset = (SCREEN_HEIGHT / 2) + mlx->_mo.y_offset;
	while (s.x < SCREEN_WIDTH)
	{
		i = draw_wall(mlx, i, offset, &s);
		draw_ceiling(&s, i, mlx);
		draw_floor(&s);
		s.x++;
	}
	mlx_put_image_to_window(mlx->p_mlx, mlx->win, s.tmp.img, 0, 0);
	mlx_destroy_image(mlx->p_mlx, s.tmp.img);
}

void	draw_doors(t_mlx *mlx)
{
	t_scene	s;
	int		i;
	int		offset;

	s.x = 0;
	s.y = 0;
	i = 0;
	s.tmp.img = mlx_new_image(mlx->p_mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	s.tmp.addr = mlx_get_data_addr(s.tmp.img, &s.tmp.bits_per_pixel,
			&s.tmp.line_length, &mlx->endian);
	offset = (SCREEN_HEIGHT / 2) + mlx->_mo.y_offset;
	while (s.x < SCREEN_WIDTH)
	{
		if (mlx->_d[s.x].door_exist)
			draw_door(&s, mlx, offset);
		else if (!mlx->_d[s.x].door_exist)
			transparence_line(0, SCREEN_HEIGHT, &s.tmp, s.x);
		s.x++;
	}
	mlx->dr_imgptr = s.tmp.img;
}

void	*test1(void *p)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)p;
	draw_doors(mlx);
	return (NULL);
}

void	*test2(void *p)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)p;
	draw_sprites(mlx);
	return (NULL);
}

void	render_scene(t_mlx *mlx)
{
	pthread_t	threads[2];

	pthread_create(&threads[1], NULL, test1, mlx);
	pthread_create(&threads[0], NULL, test2, mlx);
	draw_scene(mlx);
	pthread_join(threads[0], NULL);
	pthread_join(threads[1], NULL);
	mlx_put_image_to_window(mlx->p_mlx, mlx->win, mlx->dr_imgptr, 0, 0);
	mlx_put_image_to_window(mlx->p_mlx, mlx->win, mlx->sp_imgptr, 0, 0);
	mlx_destroy_image(mlx->p_mlx, mlx->dr_imgptr);
	mlx_destroy_image(mlx->p_mlx, mlx->sp_imgptr);
}
