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