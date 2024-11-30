NAME = cub3D
CC = gcc
CFLAGS = -Wall -Wextra -Werror #-g -fsanitize=address
MLXFLAGS = -lmlx -lXext -lX11 -lm

SRC = put_pixels_in_image.c cub3d.c player_action.c get_next_line.c get_next_line_utils.c init_data.c utils.c
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
