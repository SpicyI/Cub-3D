/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_xpms.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 00:20:38 by del-khay          #+#    #+#             */
/*   Updated: 2023/04/10 20:34:42 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

void	init_gun(t_mlx *mlx)
{
	int		frame_id;
	char	*path;

	frame_id = 0;
	mlx->crosshair.img = mlx_xpm_file_to_image(mlx->p_mlx,
			"gunxpm/crosshair.xpm", &mlx->crosshair.width,
			&mlx->crosshair.height);
	while (frame_id < 7)
	{
		path = ft_strjoin(ft_strdup("gunxpm/"), ft_itoa(frame_id + 1));
		path = ft_strjoin(path, ft_strdup(".xpm"));
		mlx->gun_frames[frame_id].img = mlx_xpm_file_to_image(mlx->p_mlx, path,
				&mlx->gun_frames[frame_id].width,
				&mlx->gun_frames[frame_id].height);
		if (!mlx->gun_frames[frame_id].img || !mlx->crosshair.img)
		{
			printf("Error reading gun frames \n");
			exit(0);
		}
		free(path);
		frame_id++;
	}
	mlx->gun_img = mlx->gun_frames[0].img;
}

void	init_loadscreen(t_mlx *mlx)
{
	int		i;
	int		j;
	int		frame_id;
	char	*path;

	frame_id = 0;
	while (frame_id < 15)
	{
		path = ft_strjoin(ft_strdup("load/"), ft_itoa(frame_id + 1));
		path = ft_strjoin(path, ft_strdup(".xpm"));
		mlx->load_screen[frame_id].img = mlx_xpm_file_to_image(mlx->p_mlx, path,
				&i, &j);
		if (mlx->load_screen[frame_id].img == NULL)
		{
			printf("Error reading gun frames \n");
			exit(0);
		}
		free(path);
		frame_id++;
	}
}

void	init_sprite(t_mlx *mlx)
{
	mlx->glitch.img = mlx_xpm_file_to_image(mlx->p_mlx,
			"testxpm/glitched.xpm", &mlx->glitch.width, &mlx->glitch.height);
	mlx->sp_img.img = mlx_xpm_file_to_image(mlx->p_mlx,
			"testxpm/holo.xpm", &mlx->sp_img.width, &mlx->sp_img.height);
	if (mlx->sp_img.img == NULL || mlx->glitch.img == NULL)
	{
		printf("Error reading sprite file \n");
		exit(0);
	}
	mlx->sp_img.addr = mlx_get_data_addr(mlx->sp_img.img,
			&mlx->sp_img.bits_per_pixel, &mlx->sp_img.line_length,
			&mlx->sp_img.endian);
	mlx->glitch.addr = mlx_get_data_addr(mlx->glitch.img,
			&mlx->glitch.bits_per_pixel, &mlx->glitch.line_length,
			&mlx->glitch.endian);
}

void	init_texture(t_mlx *mlx, t_components *comp)
{
	int	i;

	i = -1;
	mlx->_t = malloc(sizeof(t_data) * 5);
	mlx->_s = malloc(sizeof(t_side) * RAYNUMBER);
	mlx->_t[NO].img = mlx_xpm_file_to_image(mlx->p_mlx,
			comp->elements.n_texture, &mlx->_t[NO].width, &mlx->_t[NO].height);
	mlx->_t[SO].img = mlx_xpm_file_to_image(mlx->p_mlx,
			comp->elements.s_texture, &mlx->_t[SO].width, &mlx->_t[SO].height);
	mlx->_t[WE].img = mlx_xpm_file_to_image(mlx->p_mlx,
			comp->elements.w_texture, &mlx->_t[WE].width, &mlx->_t[WE].height);
	mlx->_t[EA].img = mlx_xpm_file_to_image(mlx->p_mlx,
			comp->elements.e_texture, &mlx->_t[EA].width, &mlx->_t[EA].height);
	if (mlx->_t[NO].img == NULL || mlx->_t[SO].img == NULL
		|| mlx->_t[WE].img == NULL || mlx->_t[EA].img == NULL)
	{
		printf("Error reading texture files \n");
		exit(0);
	}
	while (++i < 4)
	{
		mlx->_t[i].addr = mlx_get_data_addr(mlx->_t[i].img,
				&mlx->_t[i].bits_per_pixel, &mlx->_t[i].line_length,
				&mlx->_t[i].endian);
	}
}
