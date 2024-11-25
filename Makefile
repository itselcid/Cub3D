NAME = cub3D
CC = gcc
CFLAGS = -Wall -Wextra -Werror #-g -fsanitize=address
MLXFLAGS = -lmlx -lXext -lX11 -lm

<<<<<<< HEAD
SRC = cub3d.c player_action.c get_next_line.c get_next_line_utils.c init_data.c
=======
SRC =cub3d.c
>>>>>>> 096a364 (Add initial game setup, map rendering, and player movement logic)
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
