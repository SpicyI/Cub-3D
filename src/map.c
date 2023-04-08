/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 01:37:07 by del-khay          #+#    #+#             */
/*   Updated: 2023/04/08 02:10:02 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

int	is_wall_bloc_edge(t_bloc *t, t_mlx *mlx)
{
	if ((t->bloc_y + 1 == (t->y + 1) * mlx->_m.map_scale && (t->y
				+ 1 < mlx->_m.map_height && mlx->_m.map[t->y + 1][t->x] != '1'
			&& mlx->_m.map[t->y + 1][t->x] != 'x')) ||
		(t->bloc_x + 1 == (t->x + 1) * mlx->_m.map_scale && (t->x
					+ 1 < mlx->_m.map_width && mlx->_m.map[t->y][t->x
					+ 1] != '1' && mlx->_m.map[t->y][t->x + 1] != 'x')))
		return (TRUE);
	return (FALSE);
}

int	is_floor_bloc_edge(t_bloc *t, t_mlx *mlx)
{
	if ((t->bloc_y + 1 == (t->y + 1) * mlx->_m.map_scale && (t->y
				+ 1 < mlx->_m.map_height && mlx->_m.map[t->y
					+ 1][t->x] == '1')) ||
			(t->bloc_x + 1 == (t->x + 1) * mlx->_m.map_scale && (t->x
						+ 1 < mlx->_m.map_width && mlx->_m.map[t->y][t->x
						+ 1] == '1')))
		return (TRUE);
	return (FALSE);
}

void	draw_bloc(t_mlx *mlx, t_bloc *t)
{
	if (mlx->_m.map[t->y][t->x] != '1' && mlx->_m.map[t->y][t->x] != 'x')
	{
		if (is_floor_bloc_edge(t, mlx))
			my_mlx_pixel_put(mlx, t->bloc_x, t->bloc_y, WHITE);
		else
			my_mlx_pixel_put(mlx, t->bloc_x, t->bloc_y, FLOORCOLOR);
	}
	else if (mlx->_m.map[t->y][t->x] == '1')
	{
		if (is_wall_bloc_edge(t, mlx))
			my_mlx_pixel_put(mlx, t->bloc_x, t->bloc_y, WHITE);
		else
			my_mlx_pixel_put(mlx, t->bloc_x, t->bloc_y, WALLCOLOR);
	}
	else if (mlx->_m.map[t->y][t->x] == 'x')
		my_mlx_pixel_put(mlx, t->bloc_x, t->bloc_y, WALLCOLOR);
}

void	iterate_map(t_mlx *mlx, t_bloc *t)
{
	while (t->y < mlx->_m.map_height)
	{
		t->x = 0;
		while (t->x < mlx->_m.map_width)
		{
			t->bloc_y = t->y * mlx->_m.map_scale;
			t->bloc_x = t->x * mlx->_m.map_scale;
			while (t->bloc_y < (t->y + 1) * mlx->_m.map_scale)
			{
				while (t->bloc_x < (t->x + 1) * mlx->_m.map_scale)
				{
					draw_bloc(mlx, t);
					t->bloc_x++;
				}
				t->bloc_x = t->x * mlx->_m.map_scale;
				t->bloc_y++;
			}
			t->x++;
		}
		t->y++;
	}
}

void	draw_map(t_mlx *mlx)
{
	t_bloc	t;

	t.bloc_y = 0;
	t.bloc_x = 0;
	mlx->img = mlx_new_image(mlx->p_mlx, mlx->_m.map_width * mlx->_m.map_scale,
			mlx->_m.map_height * mlx->_m.map_scale);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel,
			&mlx->line_length, &mlx->endian);
	t.y = 0;
	iterate_map(mlx, &t);
	if (mlx->_m.display_map > 0)
	{
		crop_img(mlx, mlx->_p.player_x + 100, 0);
		crop_img(mlx, 0, mlx->_p.player_y + 100);
	}
	mlx->_m.map_img = mlx->img;
	mlx->_m.mapimg_addr = mlx->addr;
}
