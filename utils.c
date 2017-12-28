/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 17:49:23 by asarandi          #+#    #+#             */
/*   Updated: 2017/12/27 17:49:49 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		validate_input(char **input, char *pattern)
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

int		get_player_number(void)
{
	char	*input;

	if (validate_input(&input, "$$$ exec p") != 1)
		return (0);
	g_player = input[10];
	free(input);
	return (1);
}

int		get_dimensions(char *str, int *height, int *width)
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

void	write_result(void)
{
	ft_putnbr(g_result_x);
	ft_putstr(" ");
	ft_putnbr(g_result_y);
	ft_putstr("\n");
}
