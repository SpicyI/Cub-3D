/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 23:00:54 by del-khay          #+#    #+#             */
/*   Updated: 2023/03/29 04:14:01 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

int	plane_controls(int key, t_mlx *mlx)
{
    float stepX , stepY;
    stepX = cos(mlx->_p.playerAngle) * mlx->_p.movmentSpeed;
    stepY = sin(mlx->_p.playerAngle) * mlx->_p.movmentSpeed;
    
    mlx->inChange = 1;
    if (!mlx->img)
        return (0);
    if (key == 53)
		exit(0);
    if (key == 48)
    {
        mlx->_m.displayMap *= -1;
        // if (mlx->_m.displayMap  < 0)
        // {
        //     // put map in middle of the screen
        //     mlx->_m.imgPutXpos = (screenWidth / 2) - (mlx->_m.mapWidth * mlx->_m.mapScale / 2);
        //     mlx->_m.imgPutYpos = (screenHeight / 2) - (mlx->_m.mapHeight * mlx->_m.mapScale / 2);
        // }
        // else if (mlx->_m.displayMap > 0)
        // {
        //     // put map in top left corner
        //     mlx->_m.imgPutXpos = 100 - mlx->_p.playerX;
        //     mlx->_m.imgPutYpos = 100 - mlx->_p.playerY;
    }
    if (key == 123)
        mlx->_p.playerAngle -= mlx->_p.rotationSpeed;
    if (key == 124)
        mlx->_p.playerAngle += mlx->_p.rotationSpeed;
    if (key == 125)
    {
        if (mlx->_m.map[(int)mlx->_p.playerY / mlx->_m.mapScale ][(int)(mlx->_p.playerX - stepX) / mlx->_m.mapScale] != '1')
            mlx->_p.playerX -= stepX;
        if (mlx->_m.map[(int)(mlx->_p.playerY - stepY) / mlx->_m.mapScale ][(int)mlx->_p.playerX / mlx->_m.mapScale] != '1')
            mlx->_p.playerY -= stepY;
    }
    if (key == 126)
    {  
        if (mlx->_m.map[(int)mlx->_p.playerY / mlx->_m.mapScale][(int)(mlx->_p.playerX + stepX) / mlx->_m.mapScale] != '1')
            mlx->_p.playerX += stepX;
        if (mlx->_m.map[(int)(mlx->_p.playerY + stepY) / mlx->_m.mapScale][(int)mlx->_p.playerX / mlx->_m.mapScale] != '1')
            mlx->_p.playerY += stepY;
    }
	return (0);
}

// wall co