/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 19:51:24 by oel-moue          #+#    #+#             */
/*   Updated: 2025/01/04 12:46:15 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# define _USE_MATH_DEFINES
# include <fcntl.h>
# include <limits.h>
# include <float.h>
# include <math.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# define SQUAR_SIZE 50
# define MOVE_SPEED 0.015
# define ESC 65307
# define UP 119
# define DOWN 115
# define LEFT 97
# define RIGHT 100
# define ANGLE_TO_ROTATE (M_PI / 6)
# define ROTATE_RIGHT 65363
# define ROTATE_LEFT 65361
# define NUM_RAYS 120
# define FOV_ANGLE 60 * (M_PI / 180)
# define ROTATE_SPEED 0.02
# define NUM_WALL_TEXTURES 4

# define TEXTURE_WIDTH SQUAR_SIZE
#define  TEXTURE_HEIGHT SQUAR_SIZE

# define WINDOW_WIDTH 1000
# define WINDOW_HEIGHT 700

#define GREEN "\033[0;32m"
#define RESET "\033[0m"
#define RED "\033[0;31m"
typedef struct s_map
{
	int fd;
	char *line;
	char **map_data;
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

typedef enum e_texture
{
	NORTH,
	SOUTH,
	WEST,
	EAST,
}				t_e_texture;

typedef struct s_texture
{
	void		*img;
	char		*addr;
	int			width;
	int			height;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			texture_side;
	t_e_texture	tetxure;
}				t_texture;

typedef struct s_rays
{
	float		ray_angle;
	double		x_first_point_with_y_intersection;
	double		y_first_point_with_x_intersection;
	double		x_step;
	double		y_step;
	double		end_x_horizontal;
	double		end_y_horizontal;
	double		end_x_vertical;
	double		end_y_vertical;
	double		wall_hit_x;
	double		wall_hit_y;
	double		ray_distance;
	double		horizontal_distance;
	double		vertical_distance;
	int			is_ray_facing_down;
	int			is_ray_facing_up;
	int			is_ray_facing_right;
	int			is_ray_facing_left;
}				t_rays;

typedef struct s_raycas
{
	int			nbr_ray;
	t_rays		*ray;
}				t_raycas;

typedef struct s_palyer
{
	float		player_x;
	float		player_y;
	int			Movement_walk;
	int			Movement_sideways;
	int			rotate;
	float		angle;
}				t_player;

typedef struct s_image
{
	void		*img_map;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			width;
	int			height;
}				t_image;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	int			h;
	int			w;
	int			size_line;
	int         size_textures;
	t_map		*input;
	t_raycas	*raycas;
	t_player	*player;
	t_image		*img;
	t_texture	texture[NUM_WALL_TEXTURES];
}				t_data;

char			*get_next_line(int fd);
char			*ft_strdup(char *src);

int				ft_strlen(char *str);
char			*ft_strjoin(char *s1, char *s2);
char			*ft_strchr(char *str, int c);
void			init_data(t_data *data);
int				close_window(t_data *data);
int				key_handler(int key_code, t_data *data);
void			malloc_map_2D(char *filename, t_data *data);
int				ft_strlen_not_newline(char *str);
void	*ft_memset(void *b, int c, size_t len);
void			init_image(t_data *data);
int				put_color_with_pixels(t_data *data);
void			draw_player(t_data *data);
void			my_mlx_pixel_put(t_image *img, int x, int y, unsigned int color);

void	init_image_and_ray(t_data *data);
void			draw_view_from_player(t_data *data);
void			draw_line(int x1, int y1, int x2, int y2, t_data *data);
void			normalize_angle(float *angle);
float			calculate_player_angle(float player_dir_x, float player_dir_y);
void			draw_view_from_player(t_data *data);
int				key_handler(int key_code, t_data *data);
void			move_player(t_data *data);
int				relase_key(int key_code, t_data *data);
void			cast_rays(t_data *data);
void			draw_line1(t_data *data, int x1, int y1, int color);
void			ft_draw_line(t_data *data, int start_x, int start_y, int end_x,
					int end_y);
void			projection_wall(t_data *data);
// void			draw_textured_wall(t_data *data, int ray_id, int wall_start,
// 					int wall_end);
t_e_texture		determine_wall_side(t_data *data, int ray_id);
int parse_map(t_data *game, char *filename);
void init_map(t_map *map);
char	*ft_strnstr(char *haystack, char *needle, size_t len);
char	**ft_split(char  *s, char c);
int	ft_strncmp(char *s1,  char *s2, size_t n);
long	ft_atoi( char *str);
void	*ft_memcpy(void *dst,  void *src, size_t n);
char	*ft_strncpy(char *dest,  char *src, size_t n);
char	*ft_strchr( char *s, int c);
char	*ft_strjoin(char *s1, char *s2);
int	ft_strlen(char *s);
void draw_textured_wall(t_data *data, int ray_id, double wall_top, double wall_bottom, double wall_height);
// void			draw_line(t_data *data, int x1, int y1, int color);
// void			draw_line(t_data *data, int x1, int y1, int color);

#endif