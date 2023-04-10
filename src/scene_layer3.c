/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_layer3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 23:57:50 by del-khay          #+#    #+#             */
/*   Updated: 2023/04/10 01:45:38 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

void	set_sprite(int *sprite_height, t_mlx *mlx, t_scene *s)
{
	int	rst;
	int	r;

	r = 0;
	rst = s->x;
	s->s_id = mlx->_sp[s->x].sp_id;
	while (rst < SCREEN_WIDTH)
	{
		if (!mlx->_sp[rst].sprite_exist)
			break ;
		if (mlx->_sp[rst].sp_id != s->s_id)
		{
			r = -1;
			break ;
		}
		r++;
		rst++;
	}
	s->sprite_start = mlx->sp_img.width - (r * mlx->sp_img.width
			/ *sprite_height);
	s->sprite_start = ((s->sprite_start * *sprite_height) / mlx->sp_img.width);
	if (r < 0 || (rst >= SCREEN_WIDTH && r > 0))
		s->sprite_start = 0;
}

int	draw_sprite(int sprite_height, t_mlx *mlx, t_scene *s, int i)
{
	while (i < sprite_height && s->y + i < SCREEN_HEIGHT)
	{
		if (s->y + i < 0)
		{
			i++;
			continue ;
		}
		s->x_ratio = s->sprite_start * mlx->sp_img.width / sprite_height;
		s->y_ratio = i * mlx->sp_img.height / sprite_height;
		s->color = get_img_color(&(mlx->sp_img), s->x_ratio, s->y_ratio);
		my_mlx_pixel_put(&s->tmp, s->x, s->y + i, s->color);
		i++;
	}
	return (i);
}

void	put_sprite(t_scene *s, t_mlx *mlx)
{
	int	i;

	i = 0;
	s->height = (mlx->_m.map_scale / mlx->_sp[s->x].sprite_dist)
		* mlx->sreen_dist;
	s->y = s->offset - (s->height / 2);
	if (s->y + i < 0)
		i = 0 - s->y;
	transparence_line(0, s->y + i, &s->tmp, s->x);
	if (mlx->_sp[s->x].sp_id != s->s_id)
		set_sprite(&s->height, mlx, s);
	i = draw_sprite(s->height, mlx, s, i);
	transparence_line(s->y + i, SCREEN_HEIGHT, &s->tmp, s->x);
	if (s->x_ratio >= mlx->sp_img.width)
		s->sprite_start = 0;
	else
		s->sprite_start++;
}

void	draw_sprites(t_mlx *mlx)
{
	t_scene	s;

	s.offset = (SCREEN_HEIGHT / 2) + mlx->_mo.y_offset;
	s.tmp.img = mlx_new_image(mlx->p_mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	s.tmp.addr = mlx_get_data_addr(s.tmp.img, &s.tmp.bits_per_pixel,
			&s.tmp.line_length, &mlx->endian);
	s.x = 0;
	s.s_id = -1;
	s.sprite_start = 0;
	while (s.x < SCREEN_WIDTH)
	{
		if (mlx->_sp[s.x].sprite_exist)
			put_sprite(&s, mlx);
		else
		{
			transparence_line(0, SCREEN_HEIGHT, &s.tmp, s.x);
			s.sprite_start = 0;
		}
		s.x++;
	}
	mlx->sp_imgptr = s.tmp.img;
}
