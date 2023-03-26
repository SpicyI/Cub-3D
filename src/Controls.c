/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 23:00:54 by del-khay          #+#    #+#             */
/*   Updated: 2023/03/25 21:19:18 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

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
        mlx->_p.playerAngle -= mlx->_p.rotationSpeed;
    if (key == 124)
        mlx->_p.playerAngle += mlx->_p.rotationSpeed;
    if (key == 125 /*&& !isWall(key,mlx)*/)
    {
        if (mlx->_m.map[(int)mlx->_p.playerY / 30 ][(int)(mlx->_p.playerX - stepX) / 30] != '1')
            mlx->_p.playerX -= stepX;
        if (mlx->_m.map[(int)(mlx->_p.playerY - stepY) / 30 ][(int)mlx->_p.playerX /30] != '1')
            mlx->_p.playerY -= stepY;
    }
    if (key == 126 /*&& !isWall(key,mlx)*/)
    {  
        if (mlx->_m.map[(int)mlx->_p.playerY / 30][(int)(mlx->_p.playerX + stepX) / 30] != '1')
            mlx->_p.playerX += stepX;
        if (mlx->_m.map[(int)(mlx->_p.playerY + stepY) / 30][(int)mlx->_p.playerX / 30] != '1')
            mlx->_p.playerY += stepY;
    }
	return (0);
}

// wall co