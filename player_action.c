/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_action.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 10:53:58 by oel-moue          #+#    #+#             */
/*   Updated: 2024/12/01 19:11:42 by oel-moue         ###   ########.fr       */
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
}

int	close_window(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	exit(0);
	return (0);
}

// int	key_handler(int key_code, t_data *data)
// {
// 	if (key_code == ESC)
// 		close_window(data);
// 	if (key_code == DOWN)
// 		data->down = 1;
// 	if (key_code == UP)
// 		data->up = 1;
// 	if (key_code == LEFT)
// 		data->left = 1;
// 	if (key_code == RIGHT)
// 		data->right = 1;
// 	// if (key_code == ROTATE_LEFT)
// 	// 	data->rotate_left = 1;
// 	// if (key_code == ROTATE_RIGHT)
// 	// 	data->rotate_right = 1;
// 	return (0);
// }
