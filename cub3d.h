#ifndef CUB3D_H
<<<<<<< HEAD
# define CUB3D_H

# include <fcntl.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

// typedef struct s_palyer
// {
//     float player_x;
//     float player_y;
// } t_player;

typedef struct s_image
{
	void	*img0;
    void    *img1;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		width;
	int		height;
}			t_image;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	int		line_length;
	char	**map;
	int		h;
	int		up;
	int		down;
	int		left;
	int		right;
    t_image *img;
}			t_data;

char		*get_next_line(int fd);
int			ft_strlen(char *str);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_strchr(char *str, int c);
void		init_data(t_data *data);
int			close_window(t_data *data);
int			key_handler(int key_code, t_data *data);
void		malloc_map_2D(char *filename, t_data *data);

#endif
=======
#define CUB3D_H

#include <mlx.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TILE_SIZE 32
#define MAP_ROWS 10
#define MAP_COLS 15
#define WINDOW_WIDTH (TILE_SIZE * MAP_COLS)
#define WINDOW_HEIGHT (TILE_SIZE * MAP_ROWS)

#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

typedef struct s_img
{
    void *img;
    char *addr;
    int bits_per_pixel;
    int line_length;
    int endian;
} t_img;
typedef struct player
{
    int x;
    int y;
    int radius;
    int turnDirection;
    int walkDirection;
    double rotationAngle;
    double moveSpeed;
    double rotateSpeed;

} t_player;

typedef struct s_game
{
    void *mlx;
    void *win;
    t_img img;
    t_player player;
    int map[MAP_ROWS][MAP_COLS];
} t_game;

t_player init_player(void);

#endif
>>>>>>> 096a364 (Add initial game setup, map rendering, and player movement logic)
