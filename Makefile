NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror -g# -fsanitize=address
MLXFLAGS = -lmlx -lXext -lX11 -lm

SRC = projection_wall.c raycasting.c movement.c put_pixels_in_image.c cub3d.c calcule_data_map.c  get_next_line.c get_next_line_utils.c init_data.c utils.c
OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ)
	$(CC) $(OBJ)  $(CFLAGS) $(MLXFLAGS) -o $(NAME)

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
