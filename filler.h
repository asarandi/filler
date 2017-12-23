/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 18:38:26 by asarandi          #+#    #+#             */
/*   Updated: 2017/12/22 23:15:55 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H


# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <errno.h>
# include <unistd.h>
# include <fcntl.h> //open   <-- remove before submit

# define BUF_SIZE	1024


# define BUFF_SIZE 1

typedef	struct		s_gnl
{
	void			*mem;
	size_t			size;
	int				fd;
	int				eof;
	struct s_gnl	*prev;
	struct s_gnl	*next;
}					t_gnl;

int					get_next_line(const int fd, char **line);
int					write_to_file(char *filename, char *data, size_t size);
int					main();
int					quit(void);
size_t				ft_strlen(char const *s);
unsigned char		*stdin_read_eof(size_t *count);
void				ft_putstr(char const *s);
void				*ft_memalloc(size_t size);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_atoi(char *str);
int					ft_isdigit(int c);
char				*ft_strcpy(char *dst, const char *src);
void				ft_putnbr(int n);

#endif
