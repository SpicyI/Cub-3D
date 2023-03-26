/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2drendring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 22:59:47 by del-khay          #+#    #+#             */
/*   Updated: 2023/03/26 22:50:29 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

void putPlayer(t_mlx *mlx)
{
    int x = 0; // start of the rectangle (player)
    int y = 0;
    int  player_thickness = 6;
    
    mlx->img = mlx_new_image(mlx->p_mlx, screenWidth, screenHeight);
    mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel, &mlx->line_length,
                                  &mlx->endian);
    
    // draw the transparent background
    transparent_Bg(mlx);
    
    // Draw the player
    x = mlx->_p.playerX -  player_thickness / 2 ;
    while (x < mlx->_p.playerX + player_thickness / 2)
    {
        y = mlx->_p.playerY - 3;
        while (y < mlx->_p.playerY + player_thickness /2)
        {
            my_mlx_pixel_put(mlx, x, y, 0x20FFFF00);
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
    int y;
    int i = 0;
    int j = 0;

    mlx->img = mlx_new_image(mlx->p_mlx, screenWidth, screenHeight);
    mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel, &mlx->line_length,
                                         &mlx->endian);

    y = 0;

    while (y < mlx->_m.mapHeight)
    {
        x = 0;
        while (x < mlx->_m.mapWidth)
        {
            // we set block dementions
            i = y * mlx->_m.mapScale;
            j = x * mlx->_m.mapScale;
            // we draw the block
            while (i + 1 < (y + 1) * mlx->_m.mapScale)
            {
                while (j + 1 < (x + 1) * mlx->_m.mapScale)
                {
                    if (mlx->_m.map[y][x] == '1')
                        my_mlx_pixel_put(mlx, j, i, WALLCOLOR); // draw the wall
                    else
                        my_mlx_pixel_put(mlx, j, i, FLOORCOLOR); // draw the floor
                    j++;
                }
                // we reset the x axis
                j = x * mlx->_m.mapScale;
                i++;
            }
            x++;
        }
        y++;
    }
    mlx->_m.mapImg = mlx->img;
    mlx->_m.mapImgAddr = mlx->addr;
}

void putDirection(t_mlx *mlx)
{
    int x = 0;
    int y = 0;
    int line_length = mlx->_m.mapScale / 2;
    int i = 0;

    
    mlx->img = mlx_new_image(mlx->p_mlx, screenWidth, screenHeight);
    mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel, &mlx->line_length,
                                  &mlx->endian);
    
    // draw the transparent background
    transparent_Bg(mlx);
    // Draw the line
    while(i < line_length)
    {
        x = (cos(mlx->_p.playerAngle) * i) + mlx->_p.playerX;
        y = (sin(mlx->_p.playerAngle) * i) + mlx->_p.playerY;
        my_mlx_pixel_put(mlx, x, y, ARROWCOLOR);
        i++;
    }
    mlx_put_image_to_window(mlx->p_mlx, mlx->win2d, mlx->img, 0, 0);
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
    // cast the ray
    while (1)
    {
        my_mlx_pixel_put(mlx, x, y, RAYCOLOR);
        x = floor((cos(rayAngle) * i) + mlx->_p.playerX);
        if (mlx->_m.map[y / mlx->_m.mapScale][x / mlx->_m.mapScale] == '1')
            break;
        y = floor((sin(rayAngle) * i) + mlx->_p.playerY);
        if (mlx->_m.map[y / mlx->_m.mapScale][x / mlx->_m.mapScale] == '1')
            break;
        i++;
    }
    // calculate the distance and return it
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
    ray.rayNumber = RAYNUMBER;
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
            my_mlx_pixel_put(mlx, x, y, TRANSPARENT);
            y++;
        }
        x++;
    }
}

void putWalls(t_mlx * mlx)
{
    int x = 0;
    int y = 0;
    int i = 0;
    int wallHeight;
    t_mlx tmp;
    
    tmp.img = mlx_new_image(mlx->p_mlx, screenWidth, screenHeight);
    tmp.addr = mlx_get_data_addr(tmp.img, &tmp.bits_per_pixel, &tmp.line_length,
                                  &mlx->endian);

    // fill the screen column by column
    while (x < screenWidth)
    {

        // calculate the wall height
        wallHeight = (mlx->_m.mapScale / mlx->distances[x]) * SCREEN_DIST;
        if (wallHeight >= screenHeight)
            wallHeight = screenHeight;
        i = 0;
        // offset the middle of the screen
        y = (screenHeight / 2) - (wallHeight / 2);
        // draw the wall strip
        while (i < wallHeight)
        {
            my_mlx_pixel_put(&tmp, x, y + i, 0x00FFFFFF);
            i++;
        }
        x++;
    }
    mlx_put_image_to_window(mlx->p_mlx, mlx->win, tmp.img, 0, 0);
    mlx_destroy_image(mlx->p_mlx, tmp.img); 
}
