/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 10:53:41 by oel-moue          #+#    #+#             */
/*   Updated: 2024/11/29 15:29:09 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	map(t_data *data, char *file)
{
	malloc_map_2D(file, data);
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
	put_color_with_pixels(data);
}

void	move_player(t_data *data)
{
	if (data->left)
		data->player->player_x -= 1;
	if (data->right)
		data->player->player_x += 1;
	if (data->up)
		data->player->player_y -= 1;
	if (data->down)
		data->player->player_y += 1;
}
int	game_loop(t_data *data)
{
	move_player(data);
	put_color_with_pixels(data);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2 || !av[1])
	{
		printf("Error: Invalid arguments\n");
		return (1);
	}
	init_data(&data);
	map(&data, av[1]);
	mlx_hook(data.win, 17, 0, close_window, &data);
	mlx_key_hook(data.win, key_handler, &data);
	mlx_loop_hook(data.mlx, game_loop, &data);
	mlx_loop(data.mlx);
	return (0);
}
