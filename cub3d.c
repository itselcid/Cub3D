/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:31:25 by oel-moue          #+#    #+#             */
/*   Updated: 2024/12/16 20:46:06 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	calcule_first_intersection_with_x(t_data *data)
{
	double	first_intersection_by_x;

	data->raycas->y_first_point_with_x_intersection = floor(data->player->player_y
			/ SQUAR_SIZE) * SQUAR_SIZE;
	printf("player_y = %f\n", data->player->player_y);
	printf("y1 = %f\n", data->raycas->y_first_point_with_x_intersection);
	if (!data->raycas->is_ray_facing_down)
		data->raycas->y_first_point_with_x_intersection -= 1;
	first_intersection_by_x = (data->player->player_y
			- data->raycas->y_first_point_with_x_intersection)
		/ tan(data->raycas->ray_angle) + data->player->player_x;
	return (first_intersection_by_x);
}

int	calcule_first_intersection_with_y(t_data *data)
{
	double	first_intersection_by_y;

	data->raycas->x_first_point_with_y_intersection = floor(data->player->player_x
			/ SQUAR_SIZE) * SQUAR_SIZE;
	if (!data->raycas->is_ray_facing_right)
		data->raycas->x_first_point_with_y_intersection -= 1;
	first_intersection_by_y = (data->player->player_x
			- data->raycas->x_first_point_with_y_intersection)
		* tan(data->raycas->ray_angle) + data->player->player_y;
	return (first_intersection_by_y);
}

int	is_wall(float x, float y, t_data *data)
{
	int	map_x;
	int	map_y;

	map_x = floor(x / SQUAR_SIZE);
	map_y = floor(y / SQUAR_SIZE);
	if (map_y < 0 || map_y >= data->h || map_x < 0 || map_x >= data->w)
		return (1); // Consider out-of-bounds as wall
	return (data->map[map_y][map_x] == '1');
}

void	distance_horizontal(t_data *data)
{
	double x, y;
	x = calcule_first_intersection_with_x(data);
	y = data->raycas->y_first_point_with_x_intersection;
	data->raycas->y_step = SQUAR_SIZE;
	if (!data->raycas->is_ray_facing_down)
		data->raycas->y_step = -data->raycas->y_step;
	data->raycas->x_step = SQUAR_SIZE / tan(data->raycas->ray_angle);
	if (data->raycas->is_ray_facing_left)
		data->raycas->x_step = -data->raycas->x_step;
	while (!is_wall(x, y, data))
	{
		x += data->raycas->x_step;
		y += data->raycas->y_step;
	}
	data->raycas->end_x_horizontal = x;
	data->raycas->end_y_horizontal = y;
	data->raycas->distance_horizontal = sqrt(pow(x - data->player->player_x, 2)
			+ pow(y - data->player->player_y, 2));
}

void	distance_vertical(t_data *data)
{
	double x, y;
	x = calcule_first_intersection_with_y(data);
	y = data->raycas->x_first_point_with_y_intersection;
	data->raycas->x_step = SQUAR_SIZE;
	if (!data->raycas->is_ray_facing_right)
		data->raycas->x_step = -data->raycas->x_step;
	data->raycas->y_step = SQUAR_SIZE * tan(data->raycas->ray_angle);
	if (data->raycas->is_ray_facing_up)
		data->raycas->y_step = -data->raycas->y_step;
	while (!is_wall(x, y, data))
	{
		x += data->raycas->x_step;
		y += data->raycas->y_step;
	}
	data->raycas->end_x_vertical = x;
	data->raycas->end_y_vertical = y;
	data->raycas->distance_vertical = sqrt(pow(x - data->player->player_x, 2)
			+ pow(y - data->player->player_y, 2));
}

void	player_facing(t_data *data)
{
	data->raycas->is_ray_facing_down = (data->raycas->ray_angle > 0
			&& data->raycas->ray_angle < M_PI);
	data->raycas->is_ray_facing_up = !data->raycas->is_ray_facing_down;
	data->raycas->is_ray_facing_right = (data->raycas->ray_angle < 0.5 * M_PI
			|| data->raycas->ray_angle > 1.5 * M_PI);
	data->raycas->is_ray_facing_left = !data->raycas->is_ray_facing_right;
}

void	cast_ray(t_data *data)
{
	player_facing(data);
	distance_horizontal(data);
	distance_vertical(data);
	if (data->raycas->distance_horizontal < data->raycas->distance_vertical)
	{
		data->raycas->wall_hit_x = data->raycas->end_x_horizontal;
		data->raycas->wall_hit_y = data->raycas->end_y_horizontal;
		// printf("x = %f, y = %f\n", data->raycas->wall_hit_x,
			//data->raycas->wall_hit_y);
	}
	else
	{
		data->raycas->wall_hit_x = data->raycas->end_x_vertical;
		data->raycas->wall_hit_y = data->raycas->end_y_vertical;
	}
}

void	cast_rays(t_data *data)
{
	float	ray_angle;
	float	angle_step;
	float	player_base_angle;
	float	start_angle;
	int		x0;
	int		y0;
	int		end_x;
	int		end_y;

	angle_step = FOV_ANGLE / NUM_RAYS;
	player_base_angle = calculate_player_angle(data->player->player_direction_x,
			data->player->player_direction_y);
	start_angle = player_base_angle - (FOV_ANGLE / 2);
	for (int ray = 0; ray < NUM_RAYS; ray++)
	{
		ray_angle = start_angle + (angle_step * ray);
		normalize_angle(&ray_angle);
		data->raycas->ray_angle = ray_angle;
		cast_ray(data);
		x0 = data->player->player_x * SQUAR_SIZE;
		y0 = data->player->player_y * SQUAR_SIZE;
		end_x = data->raycas->wall_hit_x;
		end_y = data->raycas->wall_hit_y;
		printf("x0 = %d, y0 = %d, end_x = %d, end_y = %d\n", x0, y0, end_x,
			end_y);
		draw_line(x0, y0, end_x, end_y, data);
	}
}

int game_loop(t_data *data)
{
	//movement(data);
	put_color_with_pixels(data);
	draw_player(data);
	draw_view_from_player(data);
	//cast_rays(data);
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
