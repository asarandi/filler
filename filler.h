/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 18:38:26 by asarandi          #+#    #+#             */
/*   Updated: 2017/12/27 18:14:32 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <errno.h>
# include <unistd.h>

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

typedef	struct		s_pos
{
	int				x;
	int				y;
	int				adjacent;
	struct s_pos	*next;
}					t_pos;

char				g_player;
char				*g_plateau;
char				*g_plateau_copy;
int					g_plateau_width;
int					g_plateau_height;
char				*g_piece;
int					g_piece_width;
int					g_piece_height;
int					g_result_x;
int					g_result_y;
char				*g_slice;
char				*g_mini;
int					g_mini_height;
int					g_mini_width;
int					g_piece_top_extra;
int					g_piece_left_extra;
int					g_last_position;
int					g_mini_bottom;
int					g_mini_right;
int					g_center_x;
int					g_center_y;
int					g_distance;
int					g_enemy_x;
int					g_enemy_y;
t_pos				*g_pos;

char				*ft_strcpy(char *dst, const char *src);
char				*ft_strdup(const char *s1);
int					distance_calc(t_pos *position, int x, int y);
int					find_position(void);
int					get_next_line(const int fd, char **line);
int					gnl_main(char **memory, t_gnl **gnl, char **line);
int					gnl_more_mem(char **memory, t_gnl **gnl);
int					gnl_read(int fd, t_gnl **gnl, char **memory);
int					gnl_save(char **memory, t_gnl **gnl, char **line);
int					count_adjacent(char *slice);
int					ft_atoi(char *str);
int					ft_isdigit(int c);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
int					get_dimensions(char *str, int *height, int *width);
int					get_inputs();
int					get_piece();
int					get_plateau();
int					get_player_number();
int					main();
int					mini_bottom_extra();
int					piece_minify();
int					piece_read();
int					plateau_read();
int					plateau_slice(char *plateau);
int					trim_piece();
int					trim_piece_left(int start);
int					trim_piece_top(int start);
int					valid_collision(char c);
int					validate_input(char **input, char *pattern);
int					mini_right_extra();
int					valid_placement(char *board, char *piece);
size_t				ft_strlen(char const *s);
void				ft_putstr(char const *s);
void				ft_putnbr(int n);
void				*ft_memalloc(size_t size);
void				*ft_memchr(const void *s, int c, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				choose_position(void);
void				destroy_positions(void);
void				find_new_enemy(void);
void				save_position(int x, int y, int adjacent);
void				write_result();

#endif
