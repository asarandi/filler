NAME	= asarandi.filler
CC		= gcc
FLAGS	= -O2 -Wall -Werror -Wextra -Wno-unused-result
SRC		=	enemy.c \
			ft_putnbr.c \
			get_next_line.c \
			main.c \
			mem_op.c \
			mini.c \
			piece_util.c \
			position.c \
			read_input.c \
			string_op.c \
			utils.c \
			valid.c

OBJ		= $(SRC:%.c=%.o)

all:
	$(CC) $(FLAGS) -c $(SRC)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
