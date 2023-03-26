/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 10:52:03 by ebelkhei          #+#    #+#             */
/*   Updated: 2023/03/26 20:37:23 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

void	ft_free_all_mfs(char **str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
			free(str[i++]);
		free(str);
	}
}

static int	ft_count_words(char *str, char c)
{
	int	i;
	int	count;

	count = 0;
	if (!str)
		return (0);
	while (*str)
	{
		i = 0;
		while (str[i] && str[i] != c)
			i++;
		if (i)
		{
			count++;
			str += i;
		}
		else
		str++;
	}
	return (count);
}

static void	ft_cpychars(char *str, char **p, char c)
{
	int		len;
	int		i;
	char	**ptr;

	i = 0;
	ptr = p;
	while (str[i])
	{
		len = 0;
		while (str[i + len] && str[i + len] != c)
			len++;
		if (len)
		{
			*p = ft_substr(str, i, len);
			if (!p)
				return (ft_free_all_mfs(ptr));
			p++;
			i += len;
		}
		else
		i++;
	}
	*p = NULL;
}

char	**ft_split(char const *s, char c)
{
	char	**p;
	char	*str;

	str = (char *)s;
	if (!str)
		return (NULL);
	p = malloc((ft_count_words(str, c) + 1) * sizeof(char *));
	if (p == NULL)
		return (NULL);
	ft_cpychars(str, p, c);
	return (p);
}
