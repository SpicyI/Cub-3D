/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 22:59:39 by del-khay          #+#    #+#             */
/*   Updated: 2023/03/23 23:55:07 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.1415926535
#define mapWidthd 25
#define mapHeightd 24
#define screenWidth 720
#define screenHeight 720

typedef struct s_map
{
    char     **map;
    void    *mapImg;
    void    *mapImgAddr;
    int     mapWidth;
    int     mapHeight;
}               t_map;


typedef struct s_player
{
    float        playerX;
    float        playerY;
    float        movmentSpeed;
    float        rotationSpeed;
    float        playerAngle;
}               t_player;

typedef struct s_mlx
{
    void    *p_mlx;
    void    *win;
    void    *win2d;
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
    t_map   _m;
    t_player _p;
}               t_mlx;

/*                  mlxtools         */
void	exit_game(t_mlx *mlx);
void	my_mlx_pixel_put(t_mlx *data, int x, int y, int color);

/*                control           */
int	plane_controls(int key, t_mlx *mlx);
/*                2drendring           */
int render(t_mlx * mlx);
void putPlayer(t_mlx* mlx);
void drawMap(t_mlx *mlx);
#endif