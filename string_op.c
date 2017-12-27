/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 23:47:10 by asarandi          #+#    #+#             */
/*   Updated: 2017/12/27 03:09:21 by asarandi         ###   ########.fr       */
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

size_t			ft_strlen(char const *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

void			ft_putstr(char const *s)
{
	size_t	size;

	size = ft_strlen(s);
	write(1, s, size);
	return ;
}

int	ft_strnequ(char const *s1, char const *s2, size_t n)
{
	if ((ft_strncmp(s1, s2, n)) == 0)
		return (1);
	return (0);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;

	i = 0;
	while (i < n)
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			break ;
		if ((!s1[i]) || (!s2[i]))
			break ;
		i++;
	}
	if (i == n)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ft_atoi(char *str)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while ((str[i] >= '0') && (str[i] <= '9'))
	{
		result *= 10;
		result += str[i] - '0';
		i++;
	}
	return (result);
}

int	ft_isdigit(int c)
{
	if ((c >= '0') && (c <= '9'))
		return (1);
	else
		return (0);
}

char	*ft_strcpy(char *dst, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	return (dst);
}

