/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:27:23 by ebelkhei          #+#    #+#             */
/*   Updated: 2023/04/10 21:42:37 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

int	*parse_rgb_2(char **colors)
{
	int	i;
	int	n;
	int	*rgb;

	i = -1;
	rgb = malloc(3 * sizeof(unsigned char));
	while (colors[++i])
	{
		n = ft_atoi(colors[i]);
		if (n >= 0 && n <= 255)
			rgb[i] = n;
		else
		{
			ft_free_all_mfs(colors);
			return (NULL);
		}
	}
	return (rgb);
}

int	parse_rgb(t_elements *elements, char *color, int a)
{
	int				i;
	int				*rgb;
	char			**colors;

	colors = ft_split(color, ',');
	if (!colors || arr_size(colors) != 3 || num_of_commas(color) != 2)
		return (0);
	i = -1;
	rgb = parse_rgb_2(colors);
	if (!rgb)
		return (0);
	if (a)
	{
		elements->c_color = create_trgb(0, rgb[0], rgb[1], rgb[2]);
		elements->c = 1;
	}
	else
	{
		elements->f_color = create_trgb(0, rgb[0], rgb[1], rgb[2]);
		elements->f = 1;
	}
	free(rgb);
	ft_free_all_mfs(colors);
	return (1);
}

int	check(char **el, t_elements *elements)
{
	if ((arr_size(el) != 2))
		return (!printf("Invalid element \n"));
	if (!ft_strcmp(el[0], "NO") && !elements->n_texture)
		elements->n_texture = ft_strdup(el[1]);
	else if (!ft_strcmp(el[0], "SO") && !elements->s_texture)
		elements->s_texture = ft_strdup(el[1]);
	else if (!ft_strcmp(el[0], "WE") && !elements->w_texture)
		elements->w_texture = ft_strdup(el[1]);
	else if (!ft_strcmp(el[0], "EA") && !elements->e_texture)
		elements->e_texture = ft_strdup(el[1]);
	else if (!ft_strcmp(el[0], "F") && !elements->f)
	{
		if (!parse_rgb(elements, el[1], 0))
			return (!printf("Invalid colors\n"));
	}
	else if (!ft_strcmp(el[0], "C") && !elements->c)
	{
		if (!parse_rgb(elements, el[1], 1))
			return (!printf("Invalid colors\n"));
	}
	else
		return (!printf("Invalid element\n"));
	return (1);
}

int	check_element(char *element, t_elements *elements)
{
	char	*tmp;
	char	**el;

	tmp = element;
	if (*tmp != '\n')
	{
		element = ft_strtrim(element, "\n");
		free(tmp);
	}
	if (*element == '\n')
		return (free(element), 1);
	el = ft_split(element, ' ');
	free(element);
	if (!el)
		return (0);
	if (check(el, elements))
		return (ft_free_all_mfs(el), 1);
	return (ft_free_all_mfs(el), 0);
}

int	read_file(char *arg, t_components *comp)
{
	int		scene_file;
	char	*line;

	if (!arg || ft_strlen(arg) < 5
		|| ft_strcmp(arg + ft_strlen(arg) - 4, ".cub"))
		return (0);
	scene_file = open(arg, O_RDONLY);
	if (scene_file == -1)
		return (!printf("Invalid File\n"));
	line = get_next_line(scene_file);
	while (line && !is_map_element(line))
	{
		if (!check_element(line, &comp->elements))
			return (0);
		line = get_next_line(scene_file);
		if (!line)
			break ;
	}
	if (!line || is_dir(&comp->elements))
		return (!printf("Invalid File\n"));
	if (!read_map(scene_file, comp, line))
		return (0);
	return (check_map(comp->map, comp));
}
