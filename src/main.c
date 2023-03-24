/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 23:00:10 by del-khay          #+#    #+#             */
/*   Updated: 2023/03/24 01:23:52 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

    char *worldMap[mapWidthd]=
{
"111111111111111111111111",
"100000000000000000000001",
"100000000000000000000001",
"100000000000000000000001",
"100000111110000101010001",
"100000100010000000000001",
"100000100010000000000001",
"100000100010000100010001",
"100000110110000001010001",
"100000000000000000000001",
"100000000000000000000001",
"100000000000100000000001",
"100000000000010000000001",
"100000000000000000000001",
"100000000000000000000001",
"100000000000000000000001",
"111111111000000000000001",
"110100001000000000000001",
"110000001000000000000001",
"110100001000000000000001",
"110111111000000000000001",
"110000000000000000000001",
"111111111000000000000001",
"111111111111111111111111", 
0
};
void printmap(char *worldMap[mapWidthd])
{
    int i = 0;
    while (worldMap[i])
        printf("%s\n", worldMap[i++]);
}

void init_data(t_mlx *mlx)
{

    mlx->_m.map = worldMap;
    mlx->_m.mapWidth = mapWidthd - 1;
    mlx->_m.mapHeight = mapHeightd;
    mlx->_p.playerX = (mapWidthd / 2) * screenWidth / mapWidthd ;
    mlx->_p.playerY = (mapHeightd / 2) * screenHeight / mapHeightd;
    mlx->_p.playerAngle = PI / 2; // 90 degrees player direction
    mlx->_p.movmentSpeed = 4;
    mlx->_p.rotationSpeed = 2 *(PI / 180); // transform to radians from degrees
    
}

int main()
{
    t_mlx mlx;
    
    init_data(&mlx);
    mlx.p_mlx = mlx_init();
    // mlx.win = mlx_new_window(mlx.p_mlx, screenWidth, screenHeight, "Cub3D");
    mlx.win2d = mlx_new_window(mlx.p_mlx, screenWidth, screenHeight, "Cub2D");

    drawMap(&mlx);
    mlx_hook(mlx.win2d, 17, 0, (int (*)()) & exit_game, &mlx);
    mlx_hook(mlx.win2d, 17, 0, (int (*)()) & exit_game, &mlx);
    mlx_loop_hook(mlx.p_mlx , &render , &mlx);
    mlx_hook(mlx.win2d, 2, 0, &plane_controls, &mlx);
    dprintf(2 ,"player(%f, %f)\n", mlx._p.playerX, mlx._p.playerY);
    mlx_loop(mlx.p_mlx);


}