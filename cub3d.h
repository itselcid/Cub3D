#ifndef CUB3D_H
# define CUB3D_H
# define _USE_MATH_DEFINES
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif
# define SQUAR_SIZE 50
# define MOVE_SPEED 0.005
# define ESC 65307
# define UP 119
# define DOWN 115
# define LEFT 97
# define RIGHT 100
# define ANGLE_TO_ROTATE (M_PI / 6)
# define ROTATE_RIGHT 65363
# define ROTATE_LEFT 65361
# define NUM_RAYS 120
# define FOV_ANGLE (M_PI / 3) // 60 degree
#define ROTATE_SPEED 0.01

typedef struct s_raycas
{
	float		with_FOV;
	float		ray_angle;
	float		y_step;
	float		x_step;
	float		ray_end_x;
	float		ray_end_y;
	float 		y_first_point_with_x_intersection;
	float		x_first_point_with_y_intersection;
	float 		distance_horizontal;
	float		distance_vertical;

	float		end_x_horizontal;
	float		end_y_horizontal;
	float		end_x_vertical;
	float		end_y_vertical;
	float		wall_hit_x;
	float		wall_hit_y;
	float       is_ray_facing_down;
	float       is_ray_facing_up;
	float       is_ray_facing_right;
	float       is_ray_facing_left;

}				t_raycas;

typedef struct s_palyer
{
	float		player_x;
	float		player_y;
	int			walk;
	int			strafe;
	int			rotate;
	float       angle;
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
	char		**map;
	int			h;
	int			w;
	int			size_line;
	t_raycas	*raycas;
	t_player	*player;
	t_image		*img;
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
void			ft_memset(void *s, int c, size_t n);
void			init_image(t_data *data);
int				put_color_with_pixels(t_data *data);
void			draw_player(t_data *data);
void			my_mlx_pixel_put(t_image *img, int x, int y, int color);

void			map(t_data *data, char *file);
void			draw_view_from_player(t_data *data);
void            draw_line(int x1, int y1, int x2, int y2, t_data *data);
void            normalize_angle(float *angle);
float           calculate_player_angle(float player_dir_x, float player_dir_y);
void			draw_view_from_player(t_data *data);
int             key_handler(int key_code, t_data *data);
void            move_player(t_data *data);
int             relase_key(int key_code, t_data *data);
void            cast_rays(t_data *data);
// void			draw_fov(t_data *data);
//void			draw_line(t_data *data, int x1, int y1, int color);
//void			draw_line(t_data *data, int x1, int y1, int color);

#endif