/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 09:20:15 by ebelkhei          #+#    #+#             */
/*   Updated: 2023/04/07 00:02:05 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *ptr)
{
	char	*str;
	char	*s;
	int		i;

	s = (char *)ptr;
	str = malloc(ft_strlen(s) + 1);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_join(char *str1, char *str2)
{
	char	*nw_str;
	int		i;

	if (!str1 && !str2)
		return (NULL);
	else if (!str1)
		return (ft_strdup(str2));
	else if (!str2)
		return (ft_strdup(str1));
	nw_str = malloc(ft_strlen(str1) + ft_strlen(str2) + 1);
	if (!nw_str)
	{
		free(str1);
		return (NULL);
	}
	i = -1;
	while (str1[++i])
		nw_str[i] = str1[i];
	while (*str2)
		nw_str[i++] = *str2++;
	nw_str[i] = '\0';
	free(str1);
	return (nw_str);
}

char	*ft_strchr(const char *str, int c)
{
	char			*ptr;
	int				i;
	unsigned char	ch;

	i = 0;
	ptr = (char *)str;
	ch = c;
	if (!str)
		return (NULL);
	while (ptr[i])
	{
		if (ptr[i] == ch)
			return (ptr + i);
		i++;
	}
	if (ptr[i] == ch)
		return (ptr + i);
	return (NULL);
}

size_t	get_len(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}
