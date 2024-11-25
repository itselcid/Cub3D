#ifndef CUB3D_H
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
