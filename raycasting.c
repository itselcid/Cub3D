/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:24:52 by oel-moue          #+#    #+#             */
/*   Updated: 2024/12/17 17:33:26 by oel-moue         ###   ########.fr       */
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
    normalize_angle(&data->raycas->ray_angle);
	player_facing(data);
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

void	cast_rays(t_data *data)
{
	float	ray_angle;
	float	angle_step;
	float	start_angle;
	int		x0;
	int		y0;
	int		end_x;
	int		end_y;

	angle_step = FOV_ANGLE / NUM_RAYS;
	start_angle = data->player->angle - (FOV_ANGLE / 2);
    int ray = 0;
	while(ray < NUM_RAYS)
	{
		ray_angle = start_angle + (angle_step * ray);
		normalize_angle(&ray_angle);
		data->raycas->ray_angle = ray_angle;
		cast_ray(data);
		x0 = data->player->player_x;
		y0 = data->player->player_y;
		end_x = data->raycas->wall_hit_x;
		end_y = data->raycas->wall_hit_y;
		printf("x0 = %d, y0 = %d, end_x = %d, end_y = %d\n", x0, y0, end_x,
			end_y);
		draw_line(x0, y0, end_x, end_y, data);
        ray++;
	}
}