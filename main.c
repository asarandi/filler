/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 22:39:38 by asarandi          #+#    #+#             */
/*   Updated: 2017/12/27 18:07:39 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	free_mem(void)
{
	free(g_plateau);
	free(g_piece);
	free(g_mini);
	free(g_slice);
}

void	make_move(void)
{
	choose_position();
	write_result();
	destroy_positions();
}

int		main(void)
{
	int	r;

	g_pos = NULL;
	if (get_player_number() != 1)
		return (1);
	g_plateau_copy = NULL;
	while (get_inputs() == 1)
	{
		r = find_position();
		if (r != 0)
			make_move();
		free_mem();
		if (r == 0)
		{
			if (g_plateau_copy != NULL)
				free(g_plateau_copy);
			return (write(1, "-1 -1\n", 6));
		}
	}
	if (g_plateau_copy != NULL)
		free(g_plateau_copy);
	return (0);
}
