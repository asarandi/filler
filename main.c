/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 22:39:38 by asarandi          #+#    #+#             */
/*   Updated: 2017/12/12 18:15:58 by asarandi         ###   ########.fr       */
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
int		g_result_x;
int		g_result_y;
char	*g_slice;

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
	g_player = input[10];
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
	return ((int)ft_strlen(g_plateau) == i * g_plateau_width);
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

int	get_piece()
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

int	get_inputs()
{
	if (get_plateau() != 1)
		return (0);
	if (get_piece() != 1)
	{
		free(g_plateau);
		return (0);
	}
	if ((g_slice = ft_memalloc(g_piece_height * g_piece_width + 1)) == NULL)
	{
		free(g_plateau);
		free(g_piece);
		return (0);
	}
	return (1);
}


/*
....**
.....X

diff: * vs . is good
if diff (. vs <any>) - then ignore
if diff (* vs . `dot`) then count colisions, should be count of * (in piece) - 1 total
if diff (* vs player char) - then count, should only be one
if diff (* vs other player) then abort, move to next position
number of (diff: * vs .) should be count of (*) - 1
number of (diff: * vs


count_cells in piece, looking for '*'
compare plateau(0, 0) to string `piece`

*/

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

int valid_placement(char *board, char *piece)
{
	int	i;
	int	len;
	int collisions;

	collisions = 0;
	len = g_piece_height * g_piece_width;//ft_strlen(piece);
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

int	count_cells(char *board, char match)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while (board[i])
	{
		if (board[i] == match)
			result += 1;
		i++;
	}
	return (result);
}

int	plateau_slice(char *plateau)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = g_piece_width;
	while (i < g_piece_height)
	{
		j = 0;
		while ((j < k) && (plateau[(i * g_plateau_width) + j]))
		{
			g_slice[(i * k) + j] = plateau[(i * g_plateau_width) + j];
			j++;
		}
		if (!plateau[(i * g_plateau_width) + j])
			return (0);
		i++;
	}
	return (1);
}

int	find_position()
{
	int	i;
	int	board_size;

	i = 0;
	board_size = g_plateau_height * g_plateau_width;//ft_strlen(g_plateau);
	while (i < board_size)
	{
		if (plateau_slice(&g_plateau[i]) != 1)
			return (0);
		if (valid_placement(g_slice, g_piece) == 1)
		{
			g_result_x = i / g_plateau_width;
			g_result_y = i % g_plateau_width;
			if (g_result_y + g_piece_width <= g_plateau_width)
				return (1);
		}
		i++;
	}
	return (0);
}

void	write_result()
{
	ft_putnbr(g_result_x);
	ft_putstr(" ");
	ft_putnbr(g_result_y);
	ft_putstr("\n");
}

int	main()
{
	if (get_player_number() != 1)
		return (1);
	while (get_inputs() == 1)
	{
		// 1-call solver
		// 2-print solution
		if (find_position() == 1)
			write_result();
		else
		{
			write(1, "-1 -1\n", 6);
			return (0);
		}
		write_to_file("alex.plateau", g_plateau, ft_strlen(g_plateau));
		free(g_plateau);
		write_to_file("alex.piece", g_piece, ft_strlen(g_piece));
		free(g_piece);
		free(g_slice);
	}
	return (0);
}
