/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: del-khay <del-khay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 05:02:11 by del-khay          #+#    #+#             */
/*   Updated: 2023/04/08 05:02:55 by del-khay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*s1;
	size_t			i;

	s1 = (unsigned char *)s;
	i = 0;
	while (n--)
	{
		s1[i] = '\0';
		i++;
	}
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*p;

	if (size && nmemb > SIZE_MAX / size)
		return (0);
	p = (void *)malloc(nmemb * size);
	if (!p)
		return (0);
	ft_bzero(p, nmemb * size);
	return (p);
}

static int	arrsize(int n)
{
	unsigned int	size;

	if (n == 0)
		return (2);
	size = 1;
	while (n)
	{
		size++;
		n /= 10;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	long	nbr;
	short	size;
	char	*arr;

	size = arrsize(n);
	nbr = n;
	if (n < 0)
	{
		size++;
		nbr *= -1;
	}
	arr = (char *)malloc(sizeof(char) * size);
	if (!arr)
		return (0);
	arr[--size] = 0;
	while (--size >= 0)
	{
		arr[size] = (nbr % 10) + '0';
		nbr /= 10;
	}
	if (n < 0)
		arr[0] = '-';
	return (arr);
}

char	*ft_strjoin(char *dst, char *src)
{
	char	*rst;
	int		i;
	char	*tmp;

	i = 0;
	tmp = src;
	rst = ft_calloc(ft_strlen(dst) + ft_strlen(src) + 1, sizeof(char));
	if (!rst)
		return (0);
	while (dst && dst[i])
	{
		rst[i] = dst[i];
		i++;
	}
	while (src && *src)
		rst[i++] = *src++;
	free(dst);
	free(tmp);
	return (rst);
}
