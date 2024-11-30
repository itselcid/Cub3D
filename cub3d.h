#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif
# define SQUAR_SIZE 50
#define ROTATION_SPEED 0.1

typedef struct s_palyer
{
	float		player_x;
	float		player_y;
	float		palyer_dir_x;
	float		palyer_dir_y;
}				t_player;

typedef struct s_image
{
	void		*img_map;
	void		*img1;
	void		*img2;
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
	int			up;
	int			down;
	int			left;
	int			right;
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

#endif