NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 # -fsanitize=address
MLXFLAGS = -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

SRC = source/utils.c parsing/helpers.c parsing/ft_split.c source/put_textures.c source/projection_wall.c source/raycasting_util.c source/raycasting.c source/movement.c source/put_pixels_in_image.c \
	source/cub3d.c source/calcule_data_map.c parsing/get_next_line.c parsing/get_next_line_utils.c source/init_data.c \
	parsing/texture_parsing.c parsing/color_parsing.c parsing/map_utils.c parsing/cleanup.c \
	parsing/map_parsing.c parsing/input_parsing.c parsing/extention_validation.c parsing/ft_atoi.c
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
