/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   position.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 16:40:16 by asarandi          #+#    #+#             */
/*   Updated: 2017/12/27 16:45:41 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	save_position(int x, int y, int adjacent)
{
	t_pos	*position;
	t_pos	*new;

	position = g_pos;
	if (position != NULL)
	{
		while (position->next != NULL)
			position = position->next;
	}
	new = ft_memalloc(sizeof(t_pos));
	new->x = x;
	new->y = y;
	new->adjacent = adjacent;
	new->next = NULL;
	if (position != NULL)
		position->next = new;
	else
		g_pos = new;
}

void	destroy_positions(void)
{
	t_pos	*position;
	t_pos	*ptr;

	position = g_pos;
	while (position->next != NULL)
	{
		ptr = position->next;
		free(position);
		position = ptr;
	}
	if (position != NULL)
		free(position);
	g_pos = NULL;
}

int		find_position(void)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	i = 0;
	while (i <= g_plateau_height - g_mini_height)
	{
		j = 0;
		while (j <= g_plateau_width - g_mini_width)
		{
			if (plateau_slice(&g_plateau[i * g_plateau_width + j]) != 1)
				return (count);
			if (valid_placement(g_slice, g_mini) == 1)
			{
				g_result_x = i - g_piece_top_extra;
				g_result_y = j - g_piece_left_extra;
				save_position(g_result_x, g_result_y, count_adjacent(g_slice));
				count += 1;
			}
			j++;
		}
		i++;
	}
	return (count);
}

void	choose_position(void)
{
	int		distance;
	t_pos	*position;

	g_enemy_x = g_plateau_height / 2;
	g_enemy_y = g_plateau_width / 2;
	g_distance = 1000000;
	position = g_pos;
	if (g_plateau_copy == NULL)
		g_plateau_copy = ft_strdup(g_plateau);
	find_new_enemy();
	while (position != NULL)
	{
		distance = distance_calc(position, g_enemy_x, g_enemy_y);
		if (distance < g_distance)
		{
			g_distance = distance;
			g_result_x = position->x;
			g_result_y = position->y;
		}
		position = position->next;
	}
	ft_strcpy(g_plateau_copy, g_plateau);
}
