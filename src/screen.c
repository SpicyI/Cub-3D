/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 04:50:54 by del-khay          #+#    #+#             */
/*   Updated: 2023/04/09 03:23:49 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Cub3D.h"


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

void draw_scene(t_mlx *mlx)
{
	int		x;
	int		y;
	int		i;
	int		wallHeight;
	int 	offset;
	int 	color;
	t_mlx	tmp;

	x = 0;
	y = 0;
	i = 0;
	tmp.img = mlx_new_image(mlx->p_mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	tmp.addr = mlx_get_data_addr(tmp.img, &tmp.bits_per_pixel, &tmp.line_length,
			&mlx->endian);
	offset = (SCREEN_HEIGHT / 2) + mlx->_mo.y_offset;
	// fill the screen column by column
	while (x < SCREEN_WIDTH)
	{
		// calculate the wall height
		wallHeight = (mlx->_m.map_scale / mlx->distances[x]) * mlx->sreen_dist;
		// offset the middle of the screen
		y = offset - (wallHeight / 2);
		if(y > SCREEN_HEIGHT)
			y = SCREEN_HEIGHT;
		// draw the wall strip
		i = 0 - y;
		while (i < wallHeight && y + i < SCREEN_HEIGHT)
		{
			if (y + i < 0)
			{
				i++;
				continue;
			}
			color = get_img_color(&(mlx->_t[mlx->_s[x].tex]), mlx->_s[x].x, i * mlx->_t[mlx->_s[x].tex].height / wallHeight);
			my_mlx_pixel_put(&tmp, x, y + i, shader(color, wallHeight * 400
						/ SCREEN_HEIGHT));
			i++;
		}
		while (y + i < SCREEN_HEIGHT)
		{
			if (y + i < 0)
			{
				i++;
				continue;
			}
			my_mlx_pixel_put(&tmp, x, y + i, shader(GROUNDCOLOR, (i) * 100 / (SCREEN_HEIGHT/ 2)));
			i++;
		}
		i = 0;
		// draw the ceiling
		while (i < y && i < SCREEN_HEIGHT)
		{
			my_mlx_pixel_put(&tmp, x, i, shader(SKYCOLOR, 100 - ((i / y) * 100)));
			i++;
		}
		x++;
	}
	mlx_put_image_to_window(mlx->p_mlx, mlx->win, tmp.img, 0, 0);
	mlx_destroy_image(mlx->p_mlx, tmp.img);
}

void	putWalls(t_mlx *mlx)
{
	int		x;
	int		y;
	int		i;
	int 	offset;
	int 	s_id = -1;
	t_mlx	tmp;

	x = 0;
	y = 0;
	i = 0;
	
	draw_scene(mlx);
	offset = (SCREEN_HEIGHT / 2) + mlx->_mo.y_offset;
	tmp.img = mlx_new_image(mlx->p_mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	tmp.addr = mlx_get_data_addr(tmp.img, &tmp.bits_per_pixel, &tmp.line_length,
			&mlx->endian);
	int j = 0;
	int x_ratio;
	int y_ratio;
	int door_height;
	while (x < SCREEN_WIDTH)
	{
		
		if (mlx->_d[x].door_exist)
		{
			door_height = (mlx->_m.map_scale / mlx->_d[x].door_dist) * mlx->sreen_dist;
			y = offset - (door_height / 2);
			if(y > SCREEN_HEIGHT)
				y = SCREEN_HEIGHT;
			i = 0;
			if (y + i < 0)
				i = 0 - y;
			int  r = 0;
			while (r < y +i )
			{
				my_mlx_pixel_put(&tmp, x, r, TRANSPARENT);
				r++;
			}
			
			while (i < door_height && y + i < SCREEN_HEIGHT)
			{
				if (y + i < 0)
				{
					i++;
					continue;
				}
				if (i < (door_height * 0.05))
					my_mlx_pixel_put(&tmp, x, y + i, METAL);
				else
				my_mlx_pixel_put(&tmp, x, y + i, mlx->_d[x].door_color);
				i++;
			}
			while (y + i < SCREEN_HEIGHT)
			{
				my_mlx_pixel_put(&tmp, x, y + i, TRANSPARENT);
				i++;
			}
		}
		if(mlx->_sp[x].sprite_exist)
		{
			int sprite_height = (mlx->_m.map_scale / mlx->_sp[x].sprite_dist) * mlx->sreen_dist;
			y = offset - (sprite_height / 2);
			i = 0;
			if (y + i < 0)
				i = 0 - y;
			int  r = 0;
			while (r < y +i )
			{
				my_mlx_pixel_put(&tmp, x, r, TRANSPARENT);
				r++;
			}
			if (mlx->_sp[x].sp_id != s_id)
			{
				s_id = mlx->_sp[x].sp_id;
				 int rst = 0;
				int r = 0;
				 rst = x;
				 while(rst < SCREEN_WIDTH)
				 {
					if (!mlx->_sp[rst].sprite_exist)
						break;
					if (mlx->_sp[rst].sp_id != s_id)
					{
						r = -1;
						break;
					}
					r++;
					rst++;
				}
				j = mlx->sp_img.width - (r * mlx->sp_img.width / sprite_height);
				j = (j * sprite_height / mlx->sp_img.width);
				if (r < 0 || rst >= SCREEN_WIDTH)
					j = 0;
			}
			while (i < sprite_height && y + i < SCREEN_HEIGHT)
			{
				if (y + i < 0)
				{
					i++;
					continue;
				}
				x_ratio = j * mlx->sp_img.width / sprite_height;
				y_ratio = i * mlx->sp_img.height / sprite_height;
				int scolor = get_img_color(&(mlx->sp_img),x_ratio, y_ratio);
				//scolor = shader(scolor, 50);
				my_mlx_pixel_put(&tmp, x, y + i, scolor);
				i++;
			}
			while (y + i < SCREEN_HEIGHT)
			{
				my_mlx_pixel_put(&tmp, x, y + i, TRANSPARENT);
				i++;
			}
			if (x_ratio >= mlx->sp_img.width)
				j = 0;
			else
				j++;
		}
		if (!mlx->_sp[x].sprite_exist && !mlx->_d[x].door_exist)
		{
			i = 0;
			while (i < SCREEN_HEIGHT)
			{
				my_mlx_pixel_put(&tmp, x, i, TRANSPARENT);
				i++;
			}
			j = 0;
		}
		x++;
	}
	mlx_put_image_to_window(mlx->p_mlx, mlx->win, tmp.img, 0, 0);
	mlx_destroy_image(mlx->p_mlx, tmp.img);
}