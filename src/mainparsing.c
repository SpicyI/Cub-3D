/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainparsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 22:10:29 by ebelkhei          #+#    #+#             */
/*   Updated: 2023/04/10 02:49:42 by del-khay         ###   ########.fr       */
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
	if (!(comp->elements.n_texture && comp->elements.s_texture
			&& comp->elements.w_texture && comp->elements.e_texture
			&& comp->map))
		return (!printf("Missing Element\n"));
	return (1);
}
