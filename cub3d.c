/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 10:53:41 by oel-moue          #+#    #+#             */
/*   Updated: 2024/12/01 20:45:49 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	map(t_data *data, char *file)
{
	malloc_map_2D(file, data);
	for (int i = 0; i < data->h; i++)
	{
		for (int j = 0; j < ft_strlen_not_newline(data->map[i]); j++)
		{
			if (data->map[i][j] == 'N')
			{
				data->player->player_x = j;
				data->player->player_y = i;
				break ;
			}
		}
	}
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

// void	move_player(t_data *data)
// {
// 	if (data->up)
// 	{
// 		data->player->player_x += data->player->player_direction_x * MOVE_SPEED;
// 		data->player->player_y += data->player->player_direction_y * MOVE_SPEED;
// 	}
// 	else if (data->down)
// 	{
// 		data->player->player_x -= data->player->player_direction_x * MOVE_SPEED;
// 		data->player->player_y -= data->player->player_direction_y * MOVE_SPEED;
// 	}
// 	else if (data->left)
// 	{
// 		data->player->player_x -= data->player->player_direction_y * MOVE_SPEED;
// 		data->player->player_y += data->player->player_direction_x * MOVE_SPEED;
// 	}
// 	else if (data->right)
// 	{
// 		data->player->player_x += data->player->player_direction_y * MOVE_SPEED;
// 		data->player->player_y -= data->player->player_direction_x * MOVE_SPEED;
// 	}
// }

void move_up(t_data *data)
{
    double new_x = data->player->player_x + data->player->player_direction_x * MOVE_SPEED;
    double new_y = data->player->player_y + data->player->player_direction_y * MOVE_SPEED;

    if (data->map[(int)new_x][(int)data->player->player_y] == '0')
        data->player->player_x = new_x;
    if (data->map[(int)data->player->player_x][(int)new_y] == '0')
        data->player->player_y = new_y;
}

void move_down(t_data *data)
{
    double new_x = data->player->player_x - data->player->player_direction_x * MOVE_SPEED;
    double new_y = data->player->player_y - data->player->player_direction_y * MOVE_SPEED;

    if (data->map[(int)new_x][(int)data->player->player_y] == '0')
        data->player->player_x = new_x;
    if (data->map[(int)data->player->player_x][(int)new_y] == '0')
        data->player->player_y = new_y;
}

void move_left(t_data *data)
{
    double new_x = data->player->player_x - data->player->plane_x * MOVE_SPEED;
    double new_y = data->player->player_y - data->player->plane_y * MOVE_SPEED;

    if (data->map[(int)new_x][(int)data->player->player_y] == '0')
        data->player->player_x = new_x;
    if (data->map[(int)data->player->player_x][(int)new_y] == '0')
        data->player->player_y = new_y;
}

void move_right(t_data *data)
{
    double new_x = data->player->player_x + data->player->plane_x * MOVE_SPEED;
    double new_y = data->player->player_y + data->player->plane_y * MOVE_SPEED;

    if (data->map[(int)new_x][(int)data->player->player_y] == '0')
        data->player->player_x = new_x;
    if (data->map[(int)data->player->player_x][(int)new_y] == '0')
        data->player->player_y = new_y;
}

int	game_loop(t_data *data)
{
	//move_player(data);
	put_color_with_pixels(data);
	draw_player(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img->img_map, 0, 0);
	return (0);
}

int	key_handler(int key_code, t_data *data)
{
	if (key_code == ESC)
		close_window(data);
	if (key_code == DOWN) // s
		move_down(data);
	if (key_code == UP) // w
		move_up(data);
	if (key_code == LEFT) // a
		move_left(data);
	if (key_code == RIGHT) // d
		move_right(data);
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
