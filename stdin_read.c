/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdin_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 19:00:33 by asarandi          #+#    #+#             */
/*   Updated: 2017/12/11 02:24:24 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

unsigned char	*stdin_read_eof(size_t *count)
{
	unsigned char	*buffer;
	unsigned char	*newbuf;
	ssize_t			r;

	if ((buffer = ft_memalloc(BUF_SIZE)) == NULL)
		return (NULL);
	*count = 0;
	r = 1;
	while (r != 0)
	{
		if ((r = read(0, &buffer[*count], 1024 - (*count % 1024))) == -1)
		{
			free(buffer);
			return (NULL);
		}
		*count += r;
		if ((*count) && (*count % BUF_SIZE == 0))
		{
			if ((newbuf = ft_memalloc(*count + BUF_SIZE)) == NULL)
			{
				free(buffer);
				return (NULL);
			}
			ft_memcpy(newbuf, buffer, *count);
			free(buffer);
			buffer = newbuf;
			r = 1;
		}
	}
	return (buffer);
}
