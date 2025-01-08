/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: el_cid <el_cid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 19:51:24 by oel-moue          #+#    #+#             */
/*   Updated: 2025/01/08 23:45:32 by el_cid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# define _USE_MATH_DEFINES
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# define MOVE_SPEED 0.015
# define ESC 65307
# define UP 119
# define DOWN 115
# define LEFT 97
# define RIGHT 100
# define ANGLE_TO_ROTATE 0.523599

# define ROTATE_RIGHT 65363
# define ROTATE_LEFT 65361
# define NUM_RAYS 120
# define FOV_ANGLE 1.0472

# define ROTATE_SPEED 0.01
# define NUM_WALL_TEXTURES 4

# define WINDOW_WIDTH 1000
# define WINDOW_HEIGHT 700

# define GREEN "\033[0;32m"
# define RESET "\033[0m"
# define RED "\033[0;31m"

# define PROJECTION_PLANE_DISTANCE 866

typedef struct s_map
{
	int					fd;
	char				*line;
	char				**map_data;
	int					width;
	int					height;
	char				*no_texture;
	char				*so_texture;
	char				*we_texture;
	char				*ea_texture;
	int					floor_color[3];
	int					sky_color[3];
	int					player_x;
	int					player_y;
	char				player_dir;
}						t_map;

typedef enum e_texture
{
	NORTH,
	SOUTH,
	WEST,
	EAST,
}						t_e_texture;

typedef struct s_texture
{
	void				*img;
	char				*addr;
	int					width;
	int					height;
	int					bits_per_pixel;
	int					line_length;
	int					endian;
	int					texture_side;
	t_e_texture			tetxure;
}						t_texture;

typedef struct s_rays
{
	float				ray_angle;
	double				x_first_point;
	double				y_first_point;
	double				x_step;
	double				y_step;
	double				end_x_h;
	double				end_y_h;
	double				end_x_v;
	double				end_y_v;
	double				wall_x;
	double				wall_y;
	double				ray_distance;
	double				horizontal_distance;
	double				vertical_distance;
	int					down;
	int					up;
	int					right;
	int					left;
}						t_rays;

typedef struct s_raycas
{
	int					nbr_ray;
	t_rays				*ray;
}						t_raycas;

typedef struct s_palyer
{
	float				player_x;
	float				player_y;
	int					movement_walk;
	int					movement_sideways;
	int					rotate;
	double				angle;
}						t_player;

typedef struct s_image
{
	void				*img_map;
	char				*addr;
	int					bits_per_pixel;
	int					line_length;
	int					endian;
	int					width;
	int					height;
}						t_image;

typedef struct s_var_for_textures
{
	int					wall_top;
	int					wall_bottom;
	t_e_texture			side;
	double				wall_x;
	int					tex_x;
	double				tex_pos;
	double				step;
	int					tex_y;
}						t_var_for_textures;

typedef struct s_data
{
	void				*mlx;
	void				*win;
	int					h;
	int					w;
	int					size_line;
	int					size_textures;
	t_map				*input;
	t_raycas			*raycas;
	t_player			*player;
	t_image				*img;
	t_texture			texture[NUM_WALL_TEXTURES];
	t_var_for_textures	*var_texture;
}						t_data;

char					*get_next_line(int fd);
char					*ft_strdup(char *src);

int						ft_strlen(char *str);
char					*ft_strjoin(char *s1, char *s2);
char					*ft_strchr(char *str, int c);
void					init_data(t_data *data);
int						close_window(t_data *data);
int						key_handler(int key_code, t_data *data);
void					malloc_map_2D(char *filename, t_data *data);
int						ft_strlen_not_newline(char *str);
void					*ft_memset(void *b, int c, size_t len);
void					init_image(t_data *data);
int						put_color_with_pixels(t_data *data);
void					draw_player(t_data *data);
void					my_mlx_pixel_put(t_image *img, int x, int y,
							unsigned int color);

void					init_image_and_ray(t_data *data);
void					draw_view_from_player(t_data *data);
void					normalize_angle(double *angle);
float					calculate_player_angle(float player_dir_x,
							float player_dir_y);
void					draw_view_from_player(t_data *data);
int						key_handler(int key_code, t_data *data);
void					move_player(t_data *data);
int						relase_key(int key_code, t_data *data);
void					cast_rays(t_data *data);
void					projection_wall(t_data *data);

t_e_texture				determine_wall_side(t_data *data, int ray_id);
int						parse_map(t_data *game, char *filename);
void					init_map(t_map *map);
char					*ft_strnstr(char *haystack, char *needle, size_t len);
char					**ft_split(char *s, char c);
int						ft_strncmp(char *s1, char *s2, size_t n);
long					ft_atoi(char *str);
void					*ft_memcpy(void *dst, void *src, size_t n);
char					*ft_strncpy(char *dest, char *src, size_t n);
char					*ft_strchr(char *s, int c);
char					*ft_strjoin(char *s1, char *s2);
int						ft_strlen(char *s);
void					draw_textured_wall(t_data *game, int x,
							float wall_height, int ray_index);
double					distance_horizontal(t_data *data, int ray_id);
double					distance_vertical(t_data *data, int ray_id);
int						is_wall(double x, double y, t_data *data);
// parsing

int						parse_texture(t_data *game, char *line,
							char *direction);
int						parse_color(t_data *game, char *line, char direction);

void					cleanup_up(t_data *game, int num);
void					free_split(char **split);
char					**freemem(int i, char **result);

void					initialize_map_data(t_data *game, char *line);
int						is_valid_char(char c);
void					fill_map_spaces(t_data *game);
int						is_empty_line(char *line);
int						check_parsed_elements(t_data *game);

int						handle_map_line(t_data *game, char *line);
void					check_position(t_data *game, int y, int x);
void					validate_map(t_data *game);
int						parse_map(t_data *game, char *filename);

void					check_file(t_data *game, char *filename);
int						check_texture_extension( char *filename);

#endif