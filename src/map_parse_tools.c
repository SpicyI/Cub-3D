/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 18:00:48 by ebelkhei          #+#    #+#             */
/*   Updated: 2023/04/10 02:21:43 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

int	get_max_line(char **map)
{
	size_t	i;
	int		j;

	i = 0;
	j = 0;
	while (map[j])
	{
		if (ft_strlen(map[j]) > i)
			i = ft_strlen(map[j]);
		j++;
	}
	return (i);
}

char	*fill_map(int n, char *line)
{
	char	*str;
	int		i;

	str = malloc(n + 1);
	str[n] = 0;
	str[n - 1] = 'x';
	str[0] = 'x';
	i = 0;
	if (line)
	{
		while (line[++i - 1])
			str[i] = line[i - 1];
		i--;
	}
	while (++i < n)
		str[i] = 'x';
	return (str);
}

int	check_walls(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'x' && !check_space(map, i, j))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	is_wall_space(int a)
{
	return (a == ' ' || a == '1' || a == 'x');
}

int	check_space(char **map, int i, int j)
{
	if (map[i + 1] && map[i + 1][j] && !is_wall_space(map[i + 1][j]))
		return (!printf("Invalid Space/Wall\n"));
	if (i - 1 >= 0 && map[i - 1][j] && !is_wall_space(map[i - 1][j]))
		return (!printf("Invalid Space/Wall\n"));
	if (map[i][j + 1] && !is_wall_space(map[i][j + 1]))
		return (!printf("Invalid Space/Wall\n"));
	if (j - 1 >= 0 && map[i][j - 1] && !is_wall_space(map[i][j - 1]))
		return (!printf("Invalid Space/Wall\n"));
	return (1);
}
