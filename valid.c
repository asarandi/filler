/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 17:19:08 by asarandi          #+#    #+#             */
/*   Updated: 2017/12/27 17:19:37 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int	valid_collision(char c)
{
	if ((c != 'O') && (c != 'o') && (c != 'X') && (c != 'x'))
		return (0);
	if ((c == 'O') || (c == 'o'))
	{
		if (g_player == '2')
			return (0);
		else
			return (1);
	}
	else if ((c == 'X') || (c == 'x'))
	{
		if (g_player == '1')
			return (0);
		else
			return (1);
	}
	return (0);
}

int	valid_placement(char *board, char *piece)
{
	int	i;
	int	len;
	int collisions;

	collisions = 0;
	len = g_mini_height * g_mini_width;
	i = 0;
	while (i < len)
	{
		if ((board[i] != piece[i]) && (board[i] != '.') && (piece[i] == '*'))
		{
			if (valid_collision(board[i]) == 0)
				return (0);
			collisions += 1;
		}
		i++;
	}
	if (collisions == 1)
		return (1);
	return (0);
}
