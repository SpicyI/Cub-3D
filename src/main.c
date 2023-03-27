/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 23:00:10 by del-khay          #+#    #+#             */
/*   Updated: 2023/03/27 04:02:01 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"


void printmap(char *worldMap[mapWidthd])
{
    int i = 0;
    while (worldMap[i])
        printf("%s\n", worldMap[i++]);
}

void init_data(t_mlx *mlx , t_components *comp)
{

    mlx->distances = malloc(sizeof(float) * RAYNUMBER);
    mlx->_m.map = comp->map;
    mlx->_e = comp->elements;
    mlx->_m.mapWidth = 24;
    mlx->_m.mapHeight = 24 + 5;
    mlx->_m.mapScale = MIN(screenWidth / mlx->_m.mapWidth, screenHeight / mlx->_m.mapHeight);
    printf("mapScale = %d\n", mlx->_m.mapScale);
    mlx->_p.playerX = (11 * mlx->_m.mapScale) ;
    mlx->_p.playerY = (11 * mlx->_m.mapScale);
    mlx->_p.playerAngle = PI / 2; // 90 degrees player direction
    mlx->_p.movmentSpeed = 6;
    mlx->_p.rotationSpeed = 4 * (PI / 180); // transform to radians from degrees
    mlx->_m.displayMap = 1; // 1 = true , -1 = false
    
}

int main(int argc, char **argv)
{
    t_mlx mlx;
    t_components	comp;

	if (argc != 2)
		return (printf(YEL "Usage: ./cub3d map.cub \n" RESET));
	initialize_comps(&comp);
	if (!read_file(argv[1], &comp) || !check_comps(&comp))
		return (0);
    
    init_data(&mlx, &comp);
    mlx.p_mlx = mlx_init();
    mlx.win = mlx_new_window(mlx.p_mlx, screenWidth, screenHeight, "Cub3D");
    // mlx.win2d = mlx_new_window(mlx.p_mlx, mlx._m.mapScale *  mlx._m.mapWidth, mlx._m.mapScale * mlx._m.mapHeight, "Cub2D");

    drawMap(&mlx);
    // mlx_hook(mlx.win2d, 17, 0, (int (*)()) & exit_game, &mlx);
    mlx_hook(mlx.win, 17, 0, (int (*)()) & exit_game, &mlx);
    mlx_loop_hook(mlx.p_mlx , &render , &mlx);
    mlx_hook(mlx.win, 2, 0, &plane_controls, &mlx);
    dprintf(2 ,"player(%f, %f)\n", mlx._p.playerX, mlx._p.playerY);
    mlx_loop(mlx.p_mlx);


}