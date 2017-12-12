/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 22:39:38 by asarandi          #+#    #+#             */
/*   Updated: 2017/12/11 20:20:57 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int quit()
{
	(void)perror(strerror(errno));
	return (1);
}

char	g_player;
char	*g_plateau;
int		g_plateau_width;
int		g_plateau_height;
char	*g_piece;
int		g_piece_width;
int		g_piece_height;

int	validate_input(char **input, char *pattern)
{
	if (get_next_line(0, input) != 1)
		return (0);
	if (ft_strnequ(*input, pattern, ft_strlen(pattern)) != 1)
	{
		free(*input);
		(*input) = NULL;
		return (0);
	}
	return (1);
}

int	get_player_number()
{
	char	*input;

	if (validate_input(&input, "$$$ exec p") != 1)
		return (0);
	g_player = input[11];
	free(input);
	return (1);
}

int	get_dimensions(char *str, int *height, int *width)
{
	int	i;

	i = 0;
	*height = 0;
	*width = 0;
	while ((str[i]) && (!ft_isdigit(str[i])))
		i++;
	if (str[i])
		*height = ft_atoi(&str[i]);
	while ((str[i]) && (ft_isdigit(str[i])))
		i++;
	i += 1;
	if (str[i])
		*width = ft_atoi(&str[i]);
	free(str);
	if ((*height < 1) || (*width < 1))
		return (0);
	else
		return (1);
}

int	plateau_read()
{
	char *data;
	int	i;
	int	j;

	g_plateau = ft_memalloc(g_plateau_height * g_plateau_width + 1);
	if (g_plateau == NULL)
		return (-1);
	i = 0;
	while (i < g_plateau_height)
	{
		if (get_next_line(0, &data) != 1)
			return (0);
		j = 0;
		while ((data[j]) && (ft_isdigit(data[j])))
			j++;
		if (data[++j])
			ft_strcpy(&g_plateau[i * g_plateau_width], &data[j]);
		free(data);
		i++;
	}
	if ((int)ft_strlen(g_plateau) == i * g_plateau_width)
		return (1);
	else
		return (0);
}

int	piece_read()
{
	char *data;
	int	i;

	g_piece = ft_memalloc(g_piece_height * g_piece_width + 1);
	if (g_piece == NULL)
		return (-1);
	i = 0;
	while (i < g_piece_height)
	{
		if (get_next_line(0, &data) != 1)
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

int	get_plateau()
{
	char	*input;
	int		r;

	if (validate_input(&input, "Plateau ") != 1)
		return (0);
	if (get_dimensions(input, &g_plateau_height, &g_plateau_width) != 1)
		return (0);
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

int	get_piece()
{
	char	*input;
	int		r;

	if (validate_input(&input, "Piece ") != 1)
		return (0);
	if (get_dimensions(input, &g_piece_height, &g_piece_width) != 1)
		return (0);
	free(input);
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

int	get_inputs()
{
	if (get_plateau() != 1)
		return (0);
	if (get_piece() != 1)
		return (0);
	return (1);
}

int	main()
{
	if (get_player_number() != 1)
		return (1);
	while (get_inputs() == 1)
	{
		// 1-call solver
		// 2-print solution
		write_to_file("alex.plateau", g_plateau, ft_strlen(g_plateau));
		free(g_plateau);
		write_to_file("alex.piece", g_piece, ft_strlen(g_piece));
		free(g_piece);

	}
	return (0);
}
