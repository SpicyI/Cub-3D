/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 23:00:54 by del-khay          #+#    #+#             */
/*   Updated: 2023/03/24 21:41:30 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"


int  isWall(int key , t_mlx *mlx )
{
    int x ;
    int y ;
    float pathX = cos(mlx->_p.playerAngle);
    float pathY = sin(mlx->_p.playerAngle);
    int pathlen = 1;
    int widthScale = (screenWidth / mlx->_m.mapWidth);
    int heightScale = (screenHeight / mlx->_m.mapHeight);
    //check if the next step is a wall
    if (key == 125)
    {
        // chack the path of the player
        while (pathlen < mlx->_p.movmentSpeed)
        {
            x = floor((mlx->_p.playerX - pathX * pathlen) / widthScale);
            y = floor((mlx->_p.playerY - pathY * pathlen) / heightScale);
            if (mlx->_m.map[y][x] == '1')
                return (1);
            pathlen++;
        }
    }
    if (key == 126)
    {
        // chack the path of the player
        while (pathlen < mlx->_p.movmentSpeed)
        {
            x = floor((mlx->_p.playerX + pathX * pathlen) / widthScale);
            y = floor((mlx->_p.playerY + pathY * pathlen) / heightScale);
            if (mlx->_m.map[y][x] == '1')
                return (1);
            pathlen++;
        }
    }
    return (0);
}

int	plane_controls(int key, t_mlx *mlx)
{
    float stepX , stepY;

    stepX = cos(mlx->_p.playerAngle) * mlx->_p.movmentSpeed;
    stepY = sin(mlx->_p.playerAngle) * mlx->_p.movmentSpeed;
    
    if (!mlx->img)
        return (0);
    if (key == 53)
		exit(0);
    if (key == 123)
    {
        printf("player(%f,%f)\n",mlx->_p.playerX, mlx->_p.playerY);
        mlx_destroy_image(mlx->p_mlx, mlx->img);
        mlx->img = 0;
        mlx->_p.playerAngle -= mlx->_p.rotationSpeed;
    }
    else if (key == 124)
    {
        printf("player(%f,%f)\n",mlx->_p.playerX, mlx->_p.playerY);
        mlx_destroy_image(mlx->p_mlx, mlx->img);    
        mlx->img = 0;
        mlx->_p.playerAngle += mlx->_p.rotationSpeed;
    }
    else if (key == 125 && !isWall(key,mlx))
    {
        printf("player(%f,%f)\n",mlx->_p.playerX, mlx->_p.playerY);
        mlx_destroy_image(mlx->p_mlx, mlx->img);    
        mlx->img = 0;
        mlx->_p.playerX -= stepX;
        mlx->_p.playerY -= stepY;
    }
    else if (key == 126 && !isWall(key,mlx))
    {  
        printf("player(%f,%f)\n",mlx->_p.playerX, mlx->_p.playerY);
        mlx_destroy_image(mlx->p_mlx, mlx->img);    
        mlx->img = 0;
        mlx->_p.playerX += stepX;
        mlx->_p.playerY += stepY;
    }
	return (0);
}

// wall co