NAME = cub3D
CC = gcc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address

MLXFLAGS = -lmlx -lXext -lX11 

SRC = cub3d.c
OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) $(MLXFLAGS) -o $(NAME)

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
