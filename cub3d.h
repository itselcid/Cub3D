#ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <float.h>
#include "mlx.h"

#define WINDOW_WIDTH (MAP_COLS * SQUARE_SIZE)
#define WINDOW_HEIGHT (MAP_ROWS * SQUARE_SIZE)
#define SQUARE_SIZE 64
#define TILE_SIZE SQUARE_SIZE
#define MAP_ROWS 13
#define MAP_COLS 20
#define MAP_WIDTH MAP_COLS
#define MAP_HEIGHT MAP_ROWS
#define NUM_RAYS WINDOW_WIDTH
#define PI 3.14159265
#define FOV_ANGLE (60 * (PI / 180))
#define PROJ_DISTANCE ((WINDOW_WIDTH / 2) / tan(FOV_ANGLE / 2))

typedef struct s_ray{
    float ray_angle;
    float wall_hit_x;
    float wall_hit_y;
	float horizontal_wall_hit_x;
	float horizontal_wall_hit_y;
	float horizontal_hit_distance;
	float vertical_wall_hit_x;
	float vertical_wall_hit_y;
	float vertical_hit_distance;
    float distance;
    int is_ray_facing_up;
    int is_ray_facing_down;
    int is_ray_facing_left;
    int is_ray_facing_right;
} t_ray;

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
    t_ray rays[NUM_RAYS];    
} t_game;

extern t_game game;
extern int map[MAP_ROWS][MAP_COLS];


void ft_mlx_pixel_put(t_game *game, int x, int y, int color);
void ft_draw_line(t_game *game, int start_x, int start_y, int end_x, int end_y, int color);
void cast_ray(float ray_angle, int ray_index);
void cast_rays();
int ft_init_window(t_game *game);
void ft_initialize();
void ft_move_player();
void ft_draw_player();
void ft_draw_map();
int ft_key_press(int keycode);
int ft_key_release(int keycode);
int ft_game_loop(t_game *game);
void normalize_angle(float *angle);
int its_wall(float x, float y);
void horizontal_intersection(int ray_index);
void vertical_intersection(int ray_index);

#endif

