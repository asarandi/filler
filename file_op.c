/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 22:31:25 by asarandi          #+#    #+#             */
/*   Updated: 2017/12/11 03:05:23 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int	write_to_file(char *filename, char *data, size_t size)
{
	int		fd;

	if ((fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644)) == -1)
		return (-1);
	if ((write(fd, data, size)) == -1)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}
