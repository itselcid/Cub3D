#ifndef CUB3D_H
#define CUB3D_H
#include <stdio.h>
#include <mlx.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define WINDOW_WIDTH (MAP_COLS * SQUARE_SIZE)
#define WINDOW_HEIGHT (MAP_ROWS * SQUARE_SIZE)
#define SQUARE_SIZE 64
#define MAP_ROWS 13
#define MAP_COLS 20

#define PI 3.14159265
#define FOV_ANGLE (60 * (PI / 180))


typedef struct s_img
{
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
}   t_img;

typedef struct s_player
{
    float   x;
    float   y;
    float   width;
    float   height;
    int     turn_direction;
    int     walk_direction;
    float   rotation_angle;
    float   walk_speed;
    float   turn_speed;
}   t_player;

typedef struct s_game
{
    void *mlx;
    void *win;
    t_img img;
    t_player player;
} t_game;

#endif
