
NAME	= asarandi.filler
CC		= gcc
FLAGS	= -Wall -Werror -Wextra -O3
SRC		= $(wildcard *.c)
OBJ		= $(SRC:%.c=%.o)

all:
	$(CC) $(FLAGS) -c $(SRC)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
