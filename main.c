/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 22:39:38 by asarandi          #+#    #+#             */
/*   Updated: 2017/12/27 03:56:51 by asarandi         ###   ########.fr       */
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
char	*g_plateau_copy;
int		g_plateau_width;
int		g_plateau_height;
char	*g_piece;
int		g_piece_width;
int		g_piece_height;
int		g_result_x;
int		g_result_y;
char	*g_slice;
char	*g_mini;
int		g_mini_height;
int		g_mini_width;
int		g_piece_top_extra;
int		g_piece_left_extra;
int		g_last_position;
int		g_mini_bottom;
int		g_mini_right;


typedef	struct	s_pos
{
	int	x;
	int	y;
	int	adjacent;
	struct s_pos	*next;
}	t_pos;

t_pos	*g_pos = NULL;

int	validate_input(char **input, char *pattern)
{
	if (get_next_line(0, input) == -1)
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
	len = g_mini_height * g_mini_width;//ft_strlen(piece);
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

int	trim_piece_top(int start)
{
	int	i;
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
//	char *piece;

	i = 0;
	j = start;
//	piece = &g_piece[start];
	while (i < g_piece_height)
	{
		if (g_piece[j] != '.')
			return (0);
		j += g_piece_width;
		i += 1;
	}
	return (1);
}



int mini_right_extra()
{
	int	i;
	int	j;
	int k;

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

int	mini_bottom_extra()
{
	int i;
	int j;

	j = g_piece_width * g_piece_height - 1;
	i = j;
	while (g_piece[j] == '.')
		j--;

	return ((i - j) / g_piece_width);
}



int	piece_minify()
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


int	trim_piece()
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
//		if (!plateau[(i * g_plateau_width) + (j - 1)])
//			return (0);
		i++;
	}
	return (1);
}


void	save_position(int x, int y, int adjacent)
{
	t_pos *position;
	t_pos *new;

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

void	destroy_positions()
{
	t_pos *position;
	t_pos *ptr;

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



int	find_position()
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
			if (plateau_slice(&g_plateau[i * g_plateau_width + j ]) != 1)
				return (count);
			if (valid_placement(g_slice, g_mini) == 1)
			{
				g_result_x = i - g_piece_top_extra;
				g_result_y = j - g_piece_left_extra;
//				return (1);
				save_position(g_result_x, g_result_y, count_adjacent(g_slice));
				count += 1;
			}
			j++;
		}
		i++;
	}
	return (count);
}

void	write_result()
{
	ft_putnbr(g_result_x);
	ft_putstr(" ");
	ft_putnbr(g_result_y);
	ft_putstr("\n");
}






int	get_inputs()
{
	char *pla = "get plateau failed\n";
	char *pie = "get piece failed\n";
	char *tri = "trim piece failed\n";
	char *sli = "slice failed\n";



	if (get_plateau() != 1)
	{
		write_to_file("alex.errors", pla, ft_strlen(pla));
		return (0);
	}
	if (get_piece() != 1)
	{
		free(g_plateau);
		write_to_file("alex.errors", pie, ft_strlen(pie));

		return (0);
	}
	if (trim_piece() != 1)
	{
		write_to_file("alex.errors", tri, ft_strlen(tri));
			
		free(g_plateau);
		free(g_piece);
		return (0);
	}
	if ((g_slice = ft_memalloc(g_mini_height * g_mini_width + 1)) == NULL)
	{
		write_to_file("alex.errors", sli, ft_strlen(sli));

		free(g_plateau);
		free(g_piece);
		free(g_mini);
		return (0);
	}
	return (1);
}



int	g_center_x;
int g_center_y;
int g_distance;
int	g_enemy_x;
int	g_enemy_y;

int		distance_calc(t_pos *position, int x, int y)
{
	int	a;
	int b;

	a = position->x - x;
	a *= a;
	b = position->y - y;
	b *= b;
	return (a + b);
}

void	find_new_enemy()
{
	int i;
	int j;
	int	w;
	char c;

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
			if (g_plateau[(i * w) + j] != g_plateau_copy[(i * w) + j])
			{
				if ((g_plateau_copy[(i * w) + j] == '.') && (g_plateau[(i * w) + j] == c))
				{
					g_enemy_x = i;
					g_enemy_y = j;
					return ;
				}
			}
			j++;
		}
		i++;
	}
	return ;
}


void	choose_position()
{

	int	distance;

	g_enemy_x = g_plateau_height / 2;
	g_enemy_y = g_plateau_width / 2;
	g_distance = 1000000;

	t_pos	*position;
	position = g_pos;
//	int	adj = 100;

	if (g_plateau_copy == NULL)
		g_plateau_copy = ft_strdup(g_plateau);

	find_new_enemy();
	while (position != NULL)
	{
		distance = distance_calc(position, g_enemy_x, g_enemy_y);
//		if (position->adjacent < adj)
//		{
//			adj = position->adjacent;
//			g_distance = distance;
//			g_result_x = position->x;
//			g_result_y = position->y;
//		}
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

int	main()
{

	int	flag;

	flag = 0;

	if (get_player_number() != 1)
		return (1);
	g_last_position = 0;
	g_plateau_copy = NULL;
	while (get_inputs() == 1)
	{

		if (find_position() != 0)
		{
			g_result_x = g_pos->x;
			g_result_y = g_pos->y;
			choose_position();
			write_result();
			destroy_positions();
		}
		else
		{
//			g_last_position = 0;
			write(1, "-1 -1\n", 6);
			return (0);
		}


//		write_to_file("alex.plateau", g_plateau, ft_strlen(g_plateau));	//
//		write_to_file("alex.plateau", "\n", 1);	//
		free(g_plateau);
//		write_to_file("alex.piece", g_piece, ft_strlen(g_piece));	//
//		write_to_file("alex.piece", "\n", 1);	//
		free(g_piece);
//		write_to_file("alex.g_mini", g_piece, ft_strlen(g_piece));	//
//		write_to_file("alex.g_mini", "\n", 1);	//
		free(g_mini);
		free(g_slice);
	}
	free(g_plateau_copy);
	char *e = strerror(errno);
	write_to_file("alex.errors", e, ft_strlen(e));
	write_to_file("alex.errors", "\n", 1);
	return (0);
}
