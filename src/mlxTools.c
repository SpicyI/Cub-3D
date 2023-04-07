/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxTools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 23:00:35 by del-khay          #+#    #+#             */
/*   Updated: 2023/04/07 03:45:46 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

void	my_mlx_pixel_put(t_mlx *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x > SCREEN_WIDTH  || y < 0 || y > SCREEN_HEIGHT)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	get_img_color(t_data *data, int x, int y)
{
	char	*dst;

	if (x < 0 || x >= data->width || y < 0 || y >= data->height)
		return (0);
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	return(*(unsigned int*)dst);
}

void	exit_game(t_mlx *mlx)
{
	mlx_destroy_window(mlx->p_mlx, mlx->win);
	free(mlx->_m.map);
	free(mlx->distances);
	exit(0);
}

int	render(t_mlx *mlx)
{
	if (!mlx->on_change)
	{
		mlx_put_image_to_window(mlx->p_mlx, mlx->win,mlx->load_screen_img ,0 ,0);
		return (1);
	}
	update(mlx);
	bzero(mlx->_d, sizeof(t_data) * RAYNUMBER);
	mlx_clear_window(mlx->p_mlx, mlx->win);
	drawMap(mlx);
	mlx->img = mlx_new_image(mlx->p_mlx, mlx->_m.map_width * mlx->_m.map_scale,
			mlx->_m.map_height * mlx->_m.map_scale);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel,
			&mlx->line_length, &mlx->endian);
	transparent_Bg(mlx,mlx->_m.map_width * mlx->_m.map_scale,mlx->_m.map_height * mlx->_m.map_scale);
	ray_caster(mlx);
	mlx->_p.player_img = mlx->img;
	putWalls(mlx);
	mlx_put_image_to_window(mlx->p_mlx, mlx->win, mlx->_m.map_img,mlx->_m.img_xpos ,mlx->_m.img_ypos);
	mlx_destroy_image(mlx->p_mlx, mlx->_m.map_img);
	mlx_put_image_to_window(mlx->p_mlx, mlx->win, mlx->_p.player_img,mlx->_m.img_xpos,mlx->_m.img_ypos);
	if (mlx->_m.display_map > 0)
		mlx_put_image_to_window(mlx->p_mlx, mlx->win,mlx->gun_img, SCREEN_WIDTH - 443 , SCREEN_HEIGHT/2 - 40);
	putPlayer(mlx);
	mlx_destroy_image(mlx->p_mlx, mlx->_p.player_img);
	mlx->mouse = 0;
	mlx->_mo.mouse_angle = 0;
	return (0);
}