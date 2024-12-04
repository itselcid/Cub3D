/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 10:53:41 by oel-moue          #+#    #+#             */
/*   Updated: 2024/12/04 10:09:36 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void put_camera_with_direction_player(t_data *data)
// {
//     float x0 = data->player->player_x;
//     float y0 = data->player->player_y;
//     float x1 = x0 + data->player->player_direction_x * 10.0f;
//     float y1 = y0 + data->player->player_direction_y * 10.0f;

//     //my_mlx_pixel_put(data->img, x0, y0, 0x0000FF);
//     //draw_line(data->img, (int)x0, (int)y0, (int)x1, (int)y1, 0x00FF0000);
// }

int	game_loop(t_data *data)
{
	put_color_with_pixels(data);
	draw_player(data);
	//put_camera_with_direction_player(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img->img_map, 0, 0);
	return (0);
}

int	key_handler(int key_code, t_data *data)
{
	if (key_code == ESC)
		close_window(data);
	if (key_code == UP) // W
		move_up(data);
	if (key_code == DOWN) // S
		move_down(data);
	if (key_code == LEFT) // A
		move_left(data);
	if (key_code == RIGHT) // D
		move_right(data);
	if (key_code == ROTATE_LEFT) // <--
		rotate_direction_and_camera_left(data);
	if (key_code == ROTATE_RIGHT) // -->
		rotate_direction_and_camera_right(data);
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
	mlx_hook(data.win, 2, 1L << 0, key_handler, &data);
	mlx_loop_hook(data.mlx, game_loop, &data);
	mlx_loop(data.mlx);
	return (0);
}
