/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 21:24:11 by del-khay          #+#    #+#             */
/*   Updated: 2023/04/07 21:42:47 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

void	*framer(void *p)
{
	t_mlx	*mlx;
	int		frame;

	mlx = (t_mlx *)p;
	frame = 0;
	while (!mlx->on_change)
	{
		if (frame == 15)
			frame = 0;
		mlx->load_screen_img = mlx->load_screen[frame].img;
		usleep(100000);
		frame++;
	}
	return (NULL);
}

void	*gun_framer(void *p)
{
	t_mlx	*mlx;
	int		frame;

	frame = 0;
	mlx = (t_mlx *)p;
	while (1)
	{
		if (mlx->shoot && mlx->on_change)
		{
			while (frame < 7)
			{
				mlx->gun_img = mlx->gun_frames[frame].img;
				usleep(60000);
				frame++;
			}
			mlx->gun_img = mlx->gun_frames[0].img;
			frame = 0;
			mlx->shoot = 0;
		}
	}
}
