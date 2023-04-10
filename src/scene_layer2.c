/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_layer2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 20:36:51 by del-khay          #+#    #+#             */
/*   Updated: 2023/04/10 00:10:48 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

int	shader(int color, int shad_percentage)
{
	unsigned char	full_transparency;
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;

	full_transparency = 255;
	red = (color >> 16) & 0xFF;
	green = (color >> 8) & 0xFF;
	blue = color & 0xFF;
	if (shad_percentage > 100)
		shad_percentage = 100;
	full_transparency -= full_transparency * shad_percentage / 100;
	return (full_transparency << 24 | red << 16 | green << 8 | blue);
}

void	transparence_line(int start, int end, t_mlx *m, int x)
{
	while (start < end && start < SCREEN_HEIGHT && start >= 0)
	{
		my_mlx_pixel_put(m, x, start, TRANSPARENT);
		start++;
	}
}

void	draw_door(t_scene *s, t_mlx *mlx, int offset)
{
	int	door_height;
	int	i;

	door_height = (mlx->_m.map_scale / mlx->_d[s->x].door_dist)
		* mlx->sreen_dist;
	s->y = offset - (door_height / 2);
	if (s->y > SCREEN_HEIGHT)
		s->y = SCREEN_HEIGHT;
	i = 0;
	if (s->y + i < 0)
		i = 0 - s->y;
	transparence_line(0, s->y + i, &s->tmp, s->x);
	while (i < door_height && s->y + i < SCREEN_HEIGHT)
	{
		if (i < (door_height * 0.05))
			my_mlx_pixel_put(&s->tmp, s->x, s->y + i, METAL);
		else
			my_mlx_pixel_put(&s->tmp, s->x, s->y + i, mlx->_d[s->x].door_color);
		i++;
	}
	transparence_line(s->y + i, SCREEN_HEIGHT, &s->tmp, s->x);
}
