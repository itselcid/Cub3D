/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:31:25 by oel-moue          #+#    #+#             */
/*   Updated: 2024/12/13 11:44:39 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calcule_first_intersection_with_x(t_data *data)
{
	double	view_divise_2;

	data->raycas->y_to_fisrt_intersection = floor(data->player->player_y / SQUAR_SIZE)
		* SQUAR_SIZE;
	view_divise_2 = data->raycas->angle_view / 2;
	data->raycas->fisrt_intersection_by_x = (data->player->player_y
			- data->raycas->y_to_fisrt_intersection) / tan(view_divise_2)
		+ data->player->player_x;
}

int	is_wall(double x, double y, t_data *data)
{
	int	map_x;
	int	map_y;

	map_x = (int)x / SQUAR_SIZE;
	map_y = (int)y / SQUAR_SIZE;
	// Check if the position is within the map bounds and if it's a wall
	if (map_x >= 0 && map_y >= 0 && map_y < data->h && map_x < data->img->width
		/ SQUAR_SIZE)
	{
		return (data->map[map_y][map_x] == 1); // Assuming 1 represents a wall
	}
	return (0);
}

void calcule_distance_to_wall(t_data *data)
{
    int x;
    int y;
    double distance;

    x = data->raycas->fisrt_intersection_by_x;
	y = 
    data->raycas->y_step = SQUAR_SIZE;
    data->raycas->x_step = SQUAR_SIZE / tan(data->raycas->angle_view);
    distance = sqrt(pow(data->raycas->x_step, 2) + pow(data->raycas->y_step, 2));
    
    while (1)
    {
        if (is_wall(x, y, data))
            break;
        x += data->raycas->x_step;
        y += data->raycas->y_step;
        distance += sqrt(pow(data->raycas->x_step, 2) + pow(data->raycas->y_step, 2));
    }
	data->raycas->distance_to_wall = distance;
	data->raycas->ray_end_x = x;
    data->raycas->ray_end_y = y;
}

void	cast_rays(t_data *data)
{
	calcule_first_intersection_with_x(data);
	calcule_distance_to_wall(data);
	draw_view_from_player(data);
}

int	game_loop(t_data *data)
{
	put_color_with_pixels(data);
	draw_player(data);
	//draw_view_from_player(data);
	// draw_fov(data);
	 cast_rays(data);
	// raycasting(data);
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
