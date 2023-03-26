/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2drendring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 22:59:47 by del-khay          #+#    #+#             */
/*   Updated: 2023/03/26 02:23:06 by del-khay         ###   ########.fr       */
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
    transparent_Bg(mlx);
    
    // Draw the player
    x = mlx->_p.playerX - 4;
    while (x < mlx->_p.playerX + 4)
    {
        y = mlx->_p.playerY - 4;
        while (y < mlx->_p.playerY + 4)
        {
            my_mlx_pixel_put(mlx, x, y, 0x80FFFF00);
            y++;
        }
        x++;
    }
    
    // Draw the player
    mlx_put_image_to_window(mlx->p_mlx, mlx->win2d, mlx->img, 0, 0);
    // mlx_put_image_to_window(mlx->p_mlx, mlx->win, mlx->img, 0, 0);
    mlx_destroy_image(mlx->p_mlx, mlx->img);
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
    // mlx_put_image_to_window(mlx->p_mlx, mlx->win, mlx->img, 0, 0);
    //  save the image
    mlx->_m.mapImg = mlx->img;
    mlx->_m.mapImgAddr = mlx->addr;
}

void putDirection(t_mlx *mlx)
{
    int x = 0;
    int y = 0;

    
    mlx->img = mlx_new_image(mlx->p_mlx, screenWidth, screenHeight);
    mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel, &mlx->line_length,
                                  &mlx->endian);
    
    // draw the transparent background
    transparent_Bg(mlx);
    int line_length = MIN(screenWidth / mlx->_m.mapWidth, screenHeight / mlx->_m.mapHeight);
    int i = 0;
    // Draw the line
    while(i < line_length)
    {
        x = (cos(mlx->_p.playerAngle) * i) + mlx->_p.playerX;
        y = (sin(mlx->_p.playerAngle) * i) + mlx->_p.playerY;
        my_mlx_pixel_put(mlx, x, y, 0x00FF0000);
        i++;
    }
    mlx_put_image_to_window(mlx->p_mlx, mlx->win2d, mlx->img, 0, 0);
    // mlx_put_image_to_window(mlx->p_mlx, mlx->win, mlx->img, 0, 0);
    mlx_destroy_image(mlx->p_mlx, mlx->img);
}

float  cast(float rayAngle , t_mlx *mlx)
{
    int x;
    int y;
    int i;
    float distanceToWall;
    
    i = 0;
    x = floor((cos(rayAngle) * i) + mlx->_p.playerX);
    y = floor((sin(rayAngle) * i) + mlx->_p.playerY);
    while (1)
    {
        my_mlx_pixel_put(mlx, x, y, 0xC0022C36);
        x = floor((cos(rayAngle) * i) + mlx->_p.playerX);
        if (mlx->_m.map[y / (screenHeight / mlx->_m.mapHeight)][x / (screenWidth / mlx->_m.mapWidth)] == '1')
            break;
        y = floor((sin(rayAngle) * i) + mlx->_p.playerY);
        if (mlx->_m.map[y / (screenHeight / mlx->_m.mapHeight)][x / (screenWidth / mlx->_m.mapWidth)] == '1')
            break;
        i++;
    }
    distanceToWall = sqrt(pow(x - mlx->_p.playerX, 2) + pow(y - mlx->_p.playerY, 2));
    return(distanceToWall);
}

void rayCaster(t_mlx * mlx)
{
    mlx->img = mlx_new_image(mlx->p_mlx, screenWidth, screenHeight);
    mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel, &mlx->line_length,
                                  &mlx->endian);
    
    // draw the transparent background
    transparent_Bg(mlx);
    
    // set the ray
    t_ray ray;
    ray.startAngle = mlx->_p.playerAngle - (FOV / 2);   
    ray.endAngle = mlx->_p.playerAngle + (FOV / 2);
    ray.rayNumber = screenWidth;
    ray.step = FOV / ray.rayNumber;
    int i = 0;
    // cast the rays
    while (i < ray.rayNumber)
    {
        mlx->distances[i] = cast(ray.startAngle, mlx);
        ray.startAngle += ray.step;
        i++;
    }
    mlx_put_image_to_window(mlx->p_mlx, mlx->win2d, mlx->img, 0, 0);
    mlx_destroy_image(mlx->p_mlx, mlx->img);
}


void transparent_Bg(t_mlx *mlx)
{
    int x = 0;
    int y = 0;

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
}

void putWalls(t_mlx * mlx)
{
    int x = 0;
    int y = 0;
    float wallHeight;
    t_mlx tmp;

    tmp.img = mlx_new_image(mlx->p_mlx, screenWidth, screenHeight);
    tmp.addr = mlx_get_data_addr(tmp.img, &tmp.bits_per_pixel, &tmp.line_length,
                                  &mlx->endian);
    while (x < screenWidth)
    {
        wallHeight = WALL_HIGHT(mlx->distances[x], 30);
        if (wallHeight >= screenHeight)
            wallHeight = screenHeight - 1;
        y = (screenHeight / 2) - (wallHeight / 2);
        while (y < wallHeight)
        {
            
            if (y < 0 || y > screenHeight)
            {
                printf("y is out of screen %d \n", y);
                break;
            }
            my_mlx_pixel_put(&tmp, x, y, 0x000000FF);
            y++;
        }
        x++;
    }
    mlx_put_image_to_window(mlx->p_mlx, mlx->win, tmp.img, 0, 0);
    mlx_destroy_image(mlx->p_mlx, tmp.img); 
}
