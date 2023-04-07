/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainparsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 22:10:29 by ebelkhei          #+#    #+#             */
/*   Updated: 2023/04/07 00:39:15 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

void	initialize_comps(t_components *comp)
{
	comp->map = NULL;
	comp->player_x = 0;
	comp->map_h = 0;
	comp->map_w = 0;
	comp->player_y = 0;
	comp->elements.n_texture = NULL;
	comp->elements.s_texture = NULL;
	comp->elements.w_texture = NULL;
	comp->elements.e_texture = NULL;
	comp->elements.f_color = 0;
	comp->elements.c_color = 0;
}

int	check_comps(t_components *comp)
{
	int a = comp->elements.c_color && comp->elements.f_color
	&& comp->elements.n_texture && comp->elements.s_texture
	&& comp->elements.w_texture && comp->elements.e_texture
	&& comp->map;
	if (!a)
		return (!printf("Missing Element\n"));
	return (1);
}

void print_data(t_components *comp)
{
	int	i;

	i = 0;
	if (comp->elements.n_texture)
		printf("North: %s\n", comp->elements.n_texture);
	if (comp->elements.s_texture)
		printf("South: %s\n", comp->elements.s_texture);
	if (comp->elements.w_texture)
		printf("West: %s\n", comp->elements.w_texture);
	if (comp->elements.e_texture)
		printf("East: %s\n", comp->elements.e_texture);
	if (comp->elements.f_color)
		printf("Floor Color %d\n", comp->elements.f_color);
	if (comp->elements.c_color)
		printf("Ceil Color %d\n", comp->elements.c_color);
	printf("X: %d\n", comp->player_x);
	printf("Y: %d\n", comp->player_y);
	printf("PLAYER: %c\n", comp->map[comp->player_y][comp->player_x]);
	if (comp->map)
	{
		printf("\n-------------------------\n\n");
		while (comp->map[i])
			printf("%s\n", comp->map[i++]);
	}
	printf("map width: %d\n", comp->map_w);
	printf("map height: %d\n", comp->map_h);
}


