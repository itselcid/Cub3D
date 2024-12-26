#ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <float.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
#include "mlx.h"

// Remove these fixed definitions
// #define WINDOW_WIDTH (MAP_COLS * SQUARE_SIZE)
// #define WINDOW_HEIGHT (MAP_ROWS * SQUARE_SIZE)
// #define MAP_ROWS 13
// #define MAP_COLS 20
// #define MAP_WIDTH MAP_COLS
// #define MAP_HEIGHT MAP_ROWS

// Add these new definitions
#define SQUARE_SIZE 32
#define TILE_SIZE SQUARE_SIZE
#define NUM_RAYS 1920
#define PI 3.14159265
#define FOV_ANGLE (60 * (PI / 180))
#define PROJ_DISTANCE ((WINDOW_WIDTH / 2) / tan(FOV_ANGLE / 2))

typedef struct s_ray
{
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
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
} t_img;

typedef struct s_player
{
	float x;
	float y;
	float width;
	float height;
	int turn_direction;
	int walk_direction;
	float rotation_angle;
	float walk_speed;
	float turn_speed;
} t_player;

typedef struct s_map
{
	int fd;
	char *line;
	char **map_data;
	;
	int width;
	int height;
	char *no_texture;
	char *so_texture;
	char *we_texture;
	char *ea_texture;
	int floor_color[3];
	int sky_color[3];
	int player_x;
	int player_y;
	char player_dir;
} t_map;

typedef struct s_game
{
	void *mlx;
	void *win;
	int window_width;   
	int window_height;  
	t_map map;
	t_img img;
	t_player player;
	t_ray rays[NUM_RAYS];
} t_game;

void ft_mlx_pixel_put(t_game *game, int x, int y, int color);
void ft_draw_line(t_game *game, int start_x, int start_y, int end_x, int end_y, int color);
void cast_ray(t_game *game, float ray_angle, int ray_index);
void cast_rays(t_game *game);
int ft_init_window(t_game *game);
void ft_initialize(t_game *game);
void ft_move_player(t_game *game);
void ft_draw_player(t_game *game);
void ft_draw_map(t_game *game);
int ft_key_press(int keycode, t_game *game);
int ft_key_release(int keycode, t_game *game);
int ft_game_loop(t_game *game);
void normalize_angle(float *angle);
int its_wall(t_game *game, float x, float y);
void horizontal_intersection(t_game *game, int ray_index);
void vertical_intersection(t_game *game, int ray_index);

// parsing
void init_map(t_map *map);
int check_file_extension(t_game *game, char *filename);
int check_texture_extension(t_game *game, char *filename);
void cleanup_up(t_game *game, int num);
int parse_texture(t_game *game, char *line, char *direction);
int parse_color(t_game *game, char *line, char direction);
int parse_map(t_game *game, char *filename);
void check_position(t_game *game, int y, int x);
void validate_map(t_game *game);
void fill_map_spaces(t_game *game);
int handle_map_line(t_game *game, char *line);
int check_parsed_elements(t_game *game);

// get_next_line
#ifndef BUFFER_SIZE
#define BUFFER_SIZE 2
#endif

char *get_next_line(int fd);
char *ft_line(char *str);
char *ft_rest(char *str);
char *ft_strjoin(char *s1, char *s2);
int ft_strlen(const char *s);
char *ft_strncpy(char *dest, const char *src, size_t n);
char *ft_strchr(const char *s, int c);
char *handle_eof(int chars_readed, char *rest);
char *handle_line(char *rest);

// libft functions
int ft_strncmp(const char *s1, const char *s2, size_t n);
char *ft_strnstr(const char *haystack, const char *needle, size_t len);
char *ft_strdup(const char *s1);
char **ft_split(char const *s, char c);
long ft_atoi(const char *str);
void *ft_memset(void *b, int c, size_t len);
void *ft_memcpy(void *dst, const void *src, size_t n);

#endif
