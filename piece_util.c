/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piece_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 17:28:03 by asarandi          #+#    #+#             */
/*   Updated: 2017/12/27 17:28:27 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int	piece_minify(void)
{
	int	i;
	int	j;
	int k;

	i = g_piece_top_extra;
	k = 0;
	while (i < g_piece_height - g_mini_bottom)
	{
		j = g_piece_left_extra;
		while (j < g_piece_width - g_mini_right)
		{
			g_mini[k] = g_piece[i * g_piece_width + j];
			j++;
			k++;
		}
		i++;
	}
	return (1);
}

int	trim_piece(void)
{
	int	i;

	i = 0;
	while ((i < g_piece_height) && (trim_piece_top(i)))
		i++;
	g_piece_top_extra = i;
	i = 0;
	while ((i < g_piece_width) && (trim_piece_left(i)))
		i++;
	g_piece_left_extra = i;
	if ((g_mini = ft_memalloc(g_piece_width * g_piece_height + 1)) == NULL)
		return (0);
	g_mini_bottom = mini_bottom_extra();
	g_mini_right = mini_right_extra();
	g_mini_height = (g_piece_height - g_piece_top_extra - g_mini_bottom);
	g_mini_width = (g_piece_width - g_piece_left_extra - g_mini_right);
	piece_minify();
	return (1);
}

int	plateau_slice(char *plateau)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = g_mini_width;
	while (i < g_mini_height)
	{
		j = 0;
		while ((j < k) && (plateau[(i * g_plateau_width) + j]))
		{
			g_slice[(i * k) + j] = plateau[(i * g_plateau_width) + j];
			j++;
		}
		i++;
	}
	return (1);
}

int	count_adjacent(char *slice)
{
	char	c;
	int		i;
	int		count;

	c = 'X';
	if (g_player == '1')
		c = 'O';
	i = 0;
	count = 0;
	while (slice[i])
	{
		if (slice[i] == c)
			count++;
		i++;
	}
	return (count);
}
