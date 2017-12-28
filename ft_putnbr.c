/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 00:42:17 by asarandi          #+#    #+#             */
/*   Updated: 2017/12/27 16:58:47 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		ft_atoi(char *str)
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

int		ft_isdigit(int c)
{
	if ((c >= '0') && (c <= '9'))
		return (1);
	else
		return (0);
}

int		ft_itoa_len2(long n)
{
	int	i;

	if (n == 0)
		return (1);
	i = 0;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa2(long n, char *m)
{
	int	neg;
	int	i;

	neg = 0;
	if (n < 0)
	{
		n = -n;
		neg = 1;
	}
	i = ft_itoa_len2(n) + neg;
	m[i--] = 0;
	if (!n)
		m[i] = '0';
	while (n)
	{
		m[i--] = (n % 10) + '0';
		n /= 10;
	}
	if (neg)
		m[i] = '-';
	return (m);
}

void	ft_putnbr(int n)
{
	char	m[200];
	int		i;

	i = 0;
	while (i < 200)
		m[i++] = 0;
	ft_itoa2(n, m);
	ft_putstr(m);
}
