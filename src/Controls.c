/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 23:00:54 by del-khay          #+#    #+#             */
/*   Updated: 2023/03/24 01:34:30 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"


int  isWall(int key , t_mlx *mlx)
{
    int x = 0;
    int y = 0;
    
    if (key == 123)
    {
        x = (mlx->_p.playerX - mlx->_p.movmentSpeed) / (screenWidth / mlx->_m.mapWidth);
        y = mlx->_p.playerY / (screenHeight / mlx->_m.mapHeight);
        printf("***********************   LEFT  ***********************\n");
        printf("px = %f, py = %f\n", mlx->_p.playerX, mlx->_p.playerY);
        printf("x = %d, y = %d\n", x, y);
        if (mlx->_m.map[y][x] == '1')
        {
            printf("Wall detected! at (%d, %d)\n", x, y);
            return (1);
        }
        printf("***********************<-***********************\n");
        
    }
    else if (key == 124)
    {
        x = (mlx->_p.playerX + mlx->_p.movmentSpeed) / (screenWidth / mlx->_m.mapWidth);
        y = mlx->_p.playerY / (screenHeight / mlx->_m.mapHeight);
        printf("***********************   RIGHT  ***********************\n");
        printf("px = %f, py = %f\n", mlx->_p.playerX, mlx->_p.playerY);
        printf("x = %d, y = %d\n", x, y);
        
        if (mlx->_m.map[y][x] == '1')
        {
            printf("Wall detected! at (%d, %d)\n", x, y);
            return (1);
        }
        printf("***********************->***********************\n");
    }
    else if (key == 125)
    {
        x = mlx->_p.playerX / (screenWidth / mlx->_m.mapWidth);
        y = (mlx->_p.playerY + mlx->_p.movmentSpeed) / (screenHeight / mlx->_m.mapHeight);
        if (mlx->_m.map[y][x] == '1')
            return (1);
    }
    else if (key == 126)
    {
        x = mlx->_p.playerX / (screenWidth / mlx->_m.mapWidth);
        y = (mlx->_p.playerY - mlx->_p.movmentSpeed) / (screenHeight / mlx->_m.mapHeight);
        if (mlx->_m.map[y][x] == '1')
            return (1);
    }
    return (0);
}

int	plane_controls(int key, t_mlx *mlx)
{
    if (!mlx->img)
        return (0);
    if (key == 53)
		exit(0);
    if (key == 123 && !isWall(key,mlx))
    {
        mlx_destroy_image(mlx->p_mlx, mlx->img);
        mlx->img = 0;
        mlx->_p.playerX -= mlx->_p.movmentSpeed;
    }
    else if (key == 124 && !isWall(key,mlx))
    {
        mlx_destroy_image(mlx->p_mlx, mlx->img);    
        mlx->img = 0;
        mlx->_p.playerX += mlx->_p.movmentSpeed;
    }
    else if (key == 125 && !isWall(key,mlx))
    {
        mlx_destroy_image(mlx->p_mlx, mlx->img);    
        mlx->img = 0;
        mlx->_p.playerY += mlx->_p.movmentSpeed;
    }
    else if (key == 126 && !isWall(key,mlx) )
    {  
        mlx_destroy_image(mlx->p_mlx, mlx->img);    
        mlx->img = 0;
        mlx->_p.playerY -= mlx->_p.movmentSpeed;
    }
	return (0);
}

