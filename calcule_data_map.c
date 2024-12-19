/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcule_data_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 10:53:58 by oel-moue          #+#    #+#             */
/*   Updated: 2024/12/19 23:16:01 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	clacule_height(char *file)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		(printf("Error\n error read file\n"), exit(0));
	while ((line = get_next_line(fd)))
	{
		i++;
	}
	close(fd);
	return (i);
}

int	calcule_width(char *line)
{
	int	i;

	i = 0;
	while (line[i])
		i++;
	return (i);
}

void check_direction(t_data *data, float x, float y)
{
	char c = data->map[(int)y][(int)x];
	if  (c == 'N')
        data->player->angle = 3*M_PI / 2; // Facing up
    else if (c == 'S')
        data->player->angle = M_PI / 2; // Facing down
    else if (c == 'E')
        data->player->angle = 0; // Facing right
    else if (c == 'W')
        data->player->angle = M_PI;
}

void	position_player_and_int_map(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (y < data->h)
	{
		x = 0;
		while (data->map[y][x] != '\0')
		{
			if (data->map[y][x] == 'N' || data->map[y][x] == 'S'
				|| data->map[y][x] == 'E' || data->map[y][x] == 'W')
			{
				data->player->player_x = x ;
				data->player->player_y = y ;
				check_direction(data, x, y);
				data->map[y][x] = '0'; // Replace 'N' with '0' in mini_map
				break ;
			}
			x++;
		}
		y++;
	}
}

void	malloc_map_2D(char *filename, t_data *data)
{
	int		fd;
	int		i;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		(printf("Error\nerror read file\n"), exit(0));
	data->h = clacule_height(filename);
	data->map = malloc((data->h + 1) * sizeof(char *));
	if (data->map == NULL)
		exit(1);
	i = 0;
	while (i < data->h)
	{
		line = get_next_line(fd);
		if (line == NULL)
			(printf("Error\nerror read file\n"), exit(0));
		data->map[i] = ft_strdup(line);
		free(line);
		i++;
	}
	data->map[i] = NULL;
	close(fd);
	position_player_and_int_map(data);
}

int	close_window(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	exit(0);
	return (0);
}

void	map(t_data *data, char *file)
{
	malloc_map_2D(file, data);
	data->w = ft_strlen_not_newline(data->map[0]);
	data->img->width = ft_strlen_not_newline(data->map[0]) * SQUAR_SIZE;
	data->img->height = data->h * SQUAR_SIZE;
	data->win = mlx_new_window(data->mlx, data->img->width, data->img->height,
			"cub3D");
	if (!data->win)
	{
		printf("Error: Failed to create window\n");
		exit(0);
	}
	init_image(data);
}
