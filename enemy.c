/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 17:59:48 by asarandi          #+#    #+#             */
/*   Updated: 2017/12/27 18:38:25 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		distance_calc(t_pos *position, int x, int y)
{
	int	a;
	int b;

	a = (position->x + g_piece_top_extra) - x;
	a *= a;
	b = (position->y + g_piece_left_extra) - y;
	b *= b;
	return (a + b);
}

int		confirm_enemy(int i, int w, int j, char c)
{
	char	*pl;
	char	*plc;

	pl = g_plateau;
	plc = g_plateau_copy;
	if (pl[(i * w) + j] != plc[(i * w) + j])
	{
		if ((plc[(i * w) + j] == '.') && (pl[(i * w) + j] == c))
		{
			g_enemy_x = i;
			g_enemy_y = j;
			return (1);
		}
	}
	return (0);
}

void	find_new_enemy(void)
{
	int		i;
	int		j;
	int		w;
	char	c;

	w = g_plateau_width;
	c = 'X';
	if (g_player == '2')
		c = 'O';
	i = 0;
	while (i < g_plateau_height)
	{
		j = 0;
		while (j < g_plateau_width)
		{
			if (confirm_enemy(i, w, j, c) == 1)
				return ;
			j++;
		}
		i++;
	}
	return ;
}
