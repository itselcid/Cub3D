/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:31:25 by oel-moue          #+#    #+#             */
/*   Updated: 2024/12/12 16:08:42 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void calcule_first_intersection(t_data *data)
{
	float y_to_fisrt_intersection = 0;
	y_to_fisrt_intersection = floor(data->player->player_y / SQUAR_SIZE) * SQUAR_SIZE;
	double view_divise_2 = data->raycas->angle_view / 2; 
	data->raycas->fisrt_intersection_by_x =(data->player->player_y - y_to_fisrt_intersection) / tan(view_divise_2) + data->player->player_x;
}

// void cast_ray(t_data *data)
// {
	
// }

// void raycasting(t_data *data)
// {
// 	calcule_first_intersection(data);
// 	//cast_ray(data);
// 	printf("fisrt_intersection_by_x : %f\n", data->raycas->fisrt_intersection_by_x);
// }

int	game_loop(t_data *data)
{
	put_color_with_pixels(data);
	draw_player(data);
	draw_view_from_player(data);
	//raycasting(data);
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
