/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 19:15:55 by asarandi          #+#    #+#             */
/*   Updated: 2017/12/27 16:59:43 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

char	*ft_strdup(const char *s1)
{
	char	*mem;

	mem = (char *)malloc(sizeof(char) * ft_strlen(s1) + 1);
	if (mem == NULL)
		return (NULL);
	return (ft_strcpy(mem, s1));
}

void	*ft_memalloc(size_t size)
{
	unsigned char	*p;
	size_t			i;

	if ((p = malloc(size)) == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		p[i] = 0;
		i++;
	}
	return (p);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	size_t				i;

	d = dest;
	s = src;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (void *)(dest);
}

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*m;

	i = 0;
	m = s;
	while (i < n)
	{
		if (m[i] == (unsigned char)c)
			return (void *)(&m[i]);
		i++;
	}
	return (NULL);
}
