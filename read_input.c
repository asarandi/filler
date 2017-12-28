/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 17:22:30 by asarandi          #+#    #+#             */
/*   Updated: 2017/12/27 17:26:23 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int	plateau_read(void)
{
	char	*data;
	int		i;
	int		j;

	g_plateau = ft_memalloc(g_plateau_height * g_plateau_width + 1);
	if (g_plateau == NULL)
		return (-1);
	i = 0;
	while (i < g_plateau_height)
	{
		if (get_next_line(0, &data) == -1)
			return (0);
		j = 0;
		while ((data[j]) && (ft_isdigit(data[j])))
			j++;
		if (data[++j])
			ft_strcpy(&g_plateau[i * g_plateau_width], &data[j]);
		free(data);
		i++;
	}
	return ((int)ft_strlen(g_plateau) == i * g_plateau_width);
}

int	piece_read(void)
{
	char	*data;
	int		i;

	g_piece = ft_memalloc(g_piece_height * g_piece_width + 1);
	if (g_piece == NULL)
		return (-1);
	i = 0;
	while (i < g_piece_height)
	{
		if (get_next_line(0, &data) == -1)
			return (0);
		ft_strcpy(&g_piece[i * g_piece_width], data);
		free(data);
		i++;
	}
	if ((int)ft_strlen(g_piece) == i * g_piece_width)
		return (1);
	else
		return (0);
}

int	get_plateau(void)
{
	char	*input;
	int		r;

	if (validate_input(&input, "Plateau ") != 1)
		return (0);
	if (get_dimensions(input, &g_plateau_height, &g_plateau_width) != 1)
		return (0);
	r = get_next_line(0, &input);
	free(input);
	r = plateau_read();
	if (r == -1)
		return (0);
	else if (r == 0)
	{
		free(g_plateau);
		return (0);
	}
	return (1);
}

int	get_piece(void)
{
	char	*input;
	int		r;

	if (validate_input(&input, "Piece ") != 1)
		return (0);
	if (get_dimensions(input, &g_piece_height, &g_piece_width) != 1)
		return (0);
	r = piece_read();
	if (r == -1)
		return (0);
	else if (r == 0)
	{
		free(g_piece);
		return (0);
	}
	return (1);
}

int	get_inputs(void)
{
	if (get_plateau() != 1)
		return (0);
	if (get_piece() != 1)
	{
		free(g_plateau);
		return (0);
	}
	if (trim_piece() != 1)
	{
		free(g_plateau);
		free(g_piece);
		return (0);
	}
	if ((g_slice = ft_memalloc(g_mini_height * g_mini_width + 1)) == NULL)
	{
		free(g_plateau);
		free(g_piece);
		free(g_mini);
		return (0);
	}
	return (1);
}
