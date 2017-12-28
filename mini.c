/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 17:03:26 by asarandi          #+#    #+#             */
/*   Updated: 2017/12/27 17:04:38 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int	trim_piece_top(int start)
{
	int		i;
	char	*piece;

	i = 0;
	piece = &g_piece[start * g_piece_width];
	while (i < g_piece_width)
	{
		if (piece[i] != '.')
			return (0);
		i++;
	}
	return (1);
}

int	trim_piece_left(int start)
{
	int	i;
	int	j;

	i = 0;
	j = start;
	while (i < g_piece_height)
	{
		if (g_piece[j] != '.')
			return (0);
		j += g_piece_width;
		i += 1;
	}
	return (1);
}

int	mini_right_extra(void)
{
	int	i;
	int	j;
	int	k;

	k = 0;
	j = g_piece_width - 1;
	while (k < g_piece_width)
	{
		i = 0;
		while (i < g_piece_height)
		{
			if (g_piece[i * g_piece_width + j] != '.')
				return (k);
			i++;
		}
		k++;
		j--;
	}
	return (k);
}

int	mini_bottom_extra(void)
{
	int	i;
	int	j;

	j = g_piece_width * g_piece_height - 1;
	i = j;
	while (g_piece[j] == '.')
		j--;
	return ((i - j) / g_piece_width);
}
