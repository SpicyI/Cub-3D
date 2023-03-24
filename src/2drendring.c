/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2drendring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 22:59:47 by del-khay          #+#    #+#             */
/*   Updated: 2023/03/24 01:00:02 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

void putPlayer(t_mlx *mlx)
{
    int x = 0; // start of the rectangle (player)
    int y = 0;
    
    mlx->img = mlx_new_image(mlx->p_mlx, screenWidth, screenHeight);
    mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel, &mlx->line_length,
                                  &mlx->endian);
    
    // draw the transparent background
    while (x < screenWidth)
    {
        y = 0;
        while (y < screenHeight)
        {
            my_mlx_pixel_put(mlx, x, y, 0xFF000000);
            y++;
        }
        x++;
    }
    
    // Draw the player
    x = mlx->_p.playerX - 4;
    while (x < mlx->_p.playerX + 4)
    {
        y = mlx->_p.playerY - 4;
        while (y < mlx->_p.playerY + 4)
        {
            my_mlx_pixel_put(mlx, x, y, 0x00FFFF00);
            y++;
        }
        x++;
    }
    
    // Draw the player
    mlx_put_image_to_window(mlx->p_mlx, mlx->win2d, mlx->img, 0, 0);
    // mlx_destroy_image(mlx->p_mlx, mlx->img);
}

void drawMap(t_mlx *mlx)
{

    int x;
    int y = 0;
    int i = 0;
    int j = 0;

    mlx->img = mlx_new_image(mlx->p_mlx, screenWidth, screenHeight);
    mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel, &mlx->line_length,
                                         &mlx->endian);
    my_mlx_pixel_put(mlx, 360, 360, 0x00FF00FF);

    y = 0;

    while (y < mlx->_m.mapHeight)
    {
        x = 0;
        while (x < mlx->_m.mapWidth)
        {
            // we set block dementions
            i = y * screenHeight / mlx->_m.mapHeight;
            j = x * screenWidth / mlx->_m.mapWidth;
            // we draw the block
            while (i + 1 < (y + 1) * screenHeight / mlx->_m.mapHeight)
            {
                j = x * screenWidth / mlx->_m.mapWidth;
                while (j + 1 < (x + 1) * screenWidth / mlx->_m.mapWidth)
                {
                    if (mlx->_m.map[y][x] == '1')
                        my_mlx_pixel_put(mlx, j, i, 0x20FF90FF);
                    else
                        my_mlx_pixel_put(mlx, j, i, 0x00AED5FF); // draw the floor
                    j++;
                }
                i++;
            }
            x++;
        }
        y++;
    }
    mlx_put_image_to_window(mlx->p_mlx, mlx->win2d, mlx->img, 0, 0);
    //  save the image
    mlx->_m.mapImg = mlx->img;
    mlx->_m.mapImgAddr = mlx->addr;
}


