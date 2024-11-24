/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 10:53:41 by oel-moue          #+#    #+#             */
/*   Updated: 2024/11/24 22:41:25 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	image_to_xpm(t_data *data)
{
	int with_window = ft_strlen(data->map[0]) * 50;
	int height_window = data->h * 50 ;
	data->win = mlx_new_window(data->mlx, with_window, height_window, "Cub3D");
	if (!data->win)
	{
		printf("Error\n");
		exit(0);
	}
	data->img->img0 = mlx_xpm_file_to_image(data->mlx, "textures/floor.xpm",
			&data->img->width, &data->img->height);
	data->img->img1 = mlx_xpm_file_to_image(data->mlx, "textures/wall.xpm",
			&data->img->width, &data->img->height);
}

int	put_all_image_in_2Dmap(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < data->h)
	{
		j = 0;
		while (j < ft_strlen(data->map[i]))
		{
			mlx_put_image_to_window(data->mlx, data->win, data->img->img0, j
				* 50, i * 50);
			if (data->map[i][j] == '1') mlx_put_image_to_window(data->mlx,
				data->win, data->img->img1, j * 50, i * 50);
			j++;
		}
		i++;
	}
	return (0);
}

void	map(t_data *data, char *file)
{
	malloc_map_2D(file, data);
	image_to_xpm(data);
	put_all_image_in_2Dmap(data);
}

int	main(int ac, char **av)
{
	t_data data;
	if (ac != 2 || !av)
	{
		printf("Error input\n");
		return (0);
	}
	// parsing av[1] and file and .cub
	init_data(&data);
	map(&data, av[1]);
	mlx_key_hook(data.win, key_handler, &data);
	mlx_hook(data.win, 17, 0, close_window, &data);
	mlx_loop_hook(data.mlx, put_all_image_in_2Dmap, &data);
	mlx_loop(data.mlx);
	return (0);
}