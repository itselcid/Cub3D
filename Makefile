NAME = cub3D
CC = gcc
CFLAGS = -Wall -Wextra -Werror
MLXFLAGS = -lmlx -lXext -lX11 -lm

SRC = cub3d.c
OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ)
	$(CC) $(OBJ)  $(MLXFLAGS) -o $(NAME)

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
