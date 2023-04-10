/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 18:04:50 by ebelkhei          #+#    #+#             */
/*   Updated: 2023/04/10 02:29:14 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

int	check_map_2(char **map, t_components *comp, int player)
{
	if (!player)
		return (!printf("The Player is missing\n"));
	return (valid_space(map, comp));
}

int	create_trgb(unsigned char t, unsigned char r, unsigned char g,
		unsigned char b)
{
	return (*(int *)(unsigned char [4]){b, g, r, t});
}

int	arr_size(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

int	num_of_commas(char *str)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] == ',')
			j++;
		if (str[i] != ',' && str[i] != '\n' && !ft_isdigit(str[i]))
			exit(printf("Invalid color\n"));
	}
	return (j);
}

void	set_player_cords(t_components *comp)
{
	int	i;
	int	j;

	i = 0;
	while (comp->map[i])
	{
		j = 0;
		while (comp->map[i][j])
		{
			if (comp->map[i][j] == 32)
				comp->map[i][j] = 'x';
			if (comp->map[i][j] == 'N' || comp->map[i][j] == 'W'
				|| comp->map[i][j] == 'E' || comp->map[i][j] == 'S')
			{
				comp->player_x = j;
				comp->player_y = i;
				return ;
			}
			j++;
		}
		i++;
	}
}
