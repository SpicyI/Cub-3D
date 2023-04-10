/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_layer1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 04:34:11 by del-khay          #+#    #+#             */
/*   Updated: 2023/04/10 02:55:01 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

int	draw_wall(t_mlx *mlx, int i, int offset, t_scene *s)
{
	int	wall_height;

	wall_height = (mlx->_m.map_scale / mlx->distances[s->x]) * mlx->sreen_dist;
	s->y = offset - (wall_height / 2);
	if (s->y > SCREEN_HEIGHT)
		s->y = SCREEN_HEIGHT;
	i = 0 - s->y;
	while (i < wall_height && s->y + i < SCREEN_HEIGHT)
	{
		if (s->y + i < 0)
		{
			i++;
			continue ;
		}
		s->color = get_img_color(&(mlx->_t[mlx->_s[s->x].tex]),
				mlx->_s[s->x].x, i * mlx->_t[mlx->_s[s->x].tex].height
				/ wall_height);
		my_mlx_pixel_put(&s->tmp, s->x, s->y + i, shader(s->color, wall_height
				* 400 / SCREEN_HEIGHT));
		i++;
	}
	return (i);
}

void	draw_ceiling(t_scene *s, int i, t_mlx *mlx)
{
	while (s->y + i < SCREEN_HEIGHT)
	{
		if (s->y + i < 0)
		{
			i++;
			continue ;
		}
		my_mlx_pixel_put(&s->tmp, s->x, s->y + i, shader(mlx->_m.f_color, (i) * 100
				/ (SCREEN_HEIGHT / 2)));
		i++;
	}
}

void	draw_floor(t_scene *s)
{
	int	i;

	i = 0;
	while (i < s->y && i < SCREEN_HEIGHT)
	{
		my_mlx_pixel_put(&s->tmp, s->x, i, shader(SKYCOLOR, 100 - ((i / s->y)
					* 100)));
		i++;
	}
}
