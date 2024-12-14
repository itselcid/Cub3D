/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:31:25 by oel-moue          #+#    #+#             */
/*   Updated: 2024/12/14 19:38:24 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	calcule_first_intersection_with_x(t_data *data)
{
	double	angle;
	double	first_intersection_by_x;

	data->raycas->y_first_point_with_x_intersection = floor(data->player->player_y
			/ SQUAR_SIZE) * SQUAR_SIZE;
	angle = FOV_ANGLE / 2;
	first_intersection_by_x = (data->player->player_y
			- data->raycas->y_first_point_with_x_intersection)
		/ tan(angle) + data->player->player_x;
	return (first_intersection_by_x);
}

int	calcule_first_intersection_with_y(t_data *data)
{
	double	angle;
	double	first_intersection_by_y;

	data->raycas->x_first_point_with_y_intersection = floor(data->player->player_x
			/ SQUAR_SIZE) * SQUAR_SIZE;
	angle = FOV_ANGLE / 2;
	first_intersection_by_y = (data->player->player_x
			- data->raycas->x_first_point_with_y_intersection)
		* tan(angle) + data->player->player_y;
	return (first_intersection_by_y);
}

int	is_wall(int x, int y, t_data *data)
{
	if (x < 0 || x > data->w || y < 0 || y > data->h)
		return (1);
	if (data->map[(int)(y / SQUAR_SIZE)][(int)(x / SQUAR_SIZE)] == '1')
		return (1);
	return (0);
}

void	distance_horizontal(t_data *data)
{
	double	x;
	double	y;
	double	distance;

	x = 0;
	y = 0;
	distance = 0;
	x = calcule_first_intersection_with_x(data);
	y = data->raycas->y_first_point_with_x_intersection;
	data->raycas->y_step = SQUAR_SIZE;
	data->raycas->x_step = SQUAR_SIZE / tan(FOV_ANGLE/2);
	distance = sqrt(pow(data->raycas->x_step, 2) + pow(data->raycas->y_step,
				2));
	while (is_wall(x, y, data) == 0)
	{
		x += data->raycas->x_step;
		y += data->raycas->y_step;
		distance += sqrt(pow(data->raycas->x_step, 2)
				+ pow(data->raycas->y_step, 2));
	}
	data->raycas->end_x_horizontal = x;
	data->raycas->end_y_horizontal = y;
	data->raycas->distance_horizontal = distance;
}

void	distance_vertical(t_data *data)
{
	double	x;
	double	y;
	double	distance;

	x = calcule_first_intersection_with_y(data);
	y = data->raycas->x_first_point_with_y_intersection;
	data->raycas->x_step = SQUAR_SIZE;
	data->raycas->y_step = SQUAR_SIZE * tan(FOV_ANGLE/2);
	distance = sqrt(pow(data->raycas->x_step, 2) + pow(data->raycas->y_step,
				2));
	while (is_wall(x, y, data) == 0)
	{
		x += data->raycas->x_step;
		y += data->raycas->y_step;
		distance += sqrt(pow(data->raycas->x_step, 2)
				+ pow(data->raycas->y_step, 2));
	}
	data->raycas->end_x_vertical = x;
	data->raycas->end_y_vertical = y;
	data->raycas->distance_vertical = distance;
}


void draw_line(int x1, int y1, int x2, int y2, t_data *data)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = x1 < x2 ? 1 : -1;
    int sy = y1 < y2 ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2;
    int e2;

    while (1)
    {
        if (x1 == x2 && y1 == y2)
            break;
        if (x1 >= 0 && x1 < data->w && y1 >= 0 && y1 < data->h)
            my_mlx_pixel_put(data->img, x1, y1, 0x0000FF); // Blue color
        e2 = err;
        if (e2 > -dx) { err -= dy; x1 += sx; }
        if (e2 < dy) { err += dx; y1 += sy; }
    }
}

void	cast_ray(t_data *data)
{
	distance_horizontal(data);
	distance_vertical(data);
	if (data->raycas->distance_horizontal < data->raycas->distance_vertical)
	{
		data->raycas->wall_hit_x = data->raycas->end_x_horizontal;
		data->raycas->wall_hit_y = data->raycas->end_y_horizontal;
	}
	else
	{
		data->raycas->wall_hit_x = data->raycas->end_x_vertical;
		data->raycas->wall_hit_y = data->raycas->end_y_vertical;
	}
}

float calculate_player_angle(float player_dir_x, float player_dir_y)
{
    if (player_dir_x == 0 && player_dir_y == -1)
        return M_PI / 2; // Up
    else if (player_dir_x == 1 && player_dir_y == 0)
        return 0; // Right
    else if (player_dir_x == 0 && player_dir_y == 1)
        return 3 * M_PI / 2; // Down
    else
        return M_PI; // Left
}

void cast_rays(t_data *data)
{
    int ray;
	float angle_step = FOV_ANGLE / NUM_RAYS;
	double ray_angle;
	float player_angle = M_PI / 2; // Up
	//printf("player_angle: %f\n", player_angle);
	// in my case player angle is 0 
    double start_angle = player_angle - (FOV_ANGLE / 2);

    ray = 0;
    while (ray < NUM_RAYS)
    {
        ray_angle = start_angle + (angle_step * ray);
        data->raycas->ray_angle = ray_angle;
        cast_ray(data);
        draw_line(data->player->player_x, data->player->player_y,
                  data->raycas->wall_hit_x, data->raycas->wall_hit_y, data);
        ray++;
    }
}

int	game_loop(t_data *data)
{
	put_color_with_pixels(data);
	draw_player(data);
	//draw_view_from_player(data);
	cast_rays(data);
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
