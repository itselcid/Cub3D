/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:24:52 by oel-moue          #+#    #+#             */
/*   Updated: 2024/12/18 19:24:23 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void normalize_angle(float *angle)
// {
//     while (*angle < 0)
//         *angle += 2 * M_PI;
//     while (*angle >= 2 * M_PI)
//         *angle -= 2 * M_PI;
// }

double calcule_first_intersection_with_x(t_data *data)
{
    double first_intersection_by_x;

    if (data->raycas->is_ray_facing_down)
    {
        data->raycas->y_first_point_with_x_intersection = floor(data->player->player_y / SQUAR_SIZE) * SQUAR_SIZE + SQUAR_SIZE;
        data->raycas->y_step = SQUAR_SIZE;
    }
    else
    {
        data->raycas->y_first_point_with_x_intersection = floor(data->player->player_y / SQUAR_SIZE) * SQUAR_SIZE - 0.0001;
        data->raycas->y_step = -SQUAR_SIZE;
    }

    first_intersection_by_x = data->player->player_x + (data->raycas->y_first_point_with_x_intersection - data->player->player_y) / tan(data->raycas->ray_angle);
    data->raycas->x_step = SQUAR_SIZE / tan(data->raycas->ray_angle);

    if ((data->raycas->is_ray_facing_left && data->raycas->x_step > 0) || (data->raycas->is_ray_facing_right && data->raycas->x_step < 0))
        data->raycas->x_step = -data->raycas->x_step;

    return first_intersection_by_x;
}

double calcule_first_intersection_with_y(t_data *data)
{
    double first_intersection_by_y;

    if (data->raycas->is_ray_facing_right)
    {
        data->raycas->x_first_point_with_y_intersection = floor(data->player->player_x / SQUAR_SIZE) * SQUAR_SIZE + SQUAR_SIZE;
        data->raycas->x_step = SQUAR_SIZE;
    }
    else
    {
        data->raycas->x_first_point_with_y_intersection = floor(data->player->player_x / SQUAR_SIZE) * SQUAR_SIZE - 0.0001;
        data->raycas->x_step = -SQUAR_SIZE;
    }

    first_intersection_by_y = data->player->player_y + (data->raycas->x_first_point_with_y_intersection - data->player->player_x) * tan(data->raycas->ray_angle);
    data->raycas->y_step = SQUAR_SIZE * tan(data->raycas->ray_angle);

    if ((data->raycas->is_ray_facing_up && data->raycas->y_step > 0) || (data->raycas->is_ray_facing_down && data->raycas->y_step < 0))
        data->raycas->y_step = -data->raycas->y_step;

    return first_intersection_by_y;
}

int is_wall(double x, double y, t_data *data)
{
	int i;
	int j;

	i = floor(x / SQUAR_SIZE);
	j = floor(y / SQUAR_SIZE);

	if (i < 0 || i >= data->w || j < 0 || j >= data->h)
		return (1);
	if (data->map[j][i] == '1')
		return (1);
	return (0);
}
void distance_horizontal(t_data *data)
{
    double x, y;
    x = calcule_first_intersection_with_x(data);
    y = data->raycas->y_first_point_with_x_intersection;

    while (!is_wall(x, y, data))
    {
        x += data->raycas->x_step;
        y += data->raycas->y_step;
    }

    data->raycas->end_x_horizontal = x;
    data->raycas->end_y_horizontal = y;
    data->raycas->distance_horizontal = sqrt(pow(x - data->player->player_x, 2) + pow(y - data->player->player_y, 2));
}

void distance_vertical(t_data *data)
{
    double x, y;
    x = calcule_first_intersection_with_y(data);
    y = data->raycas->x_first_point_with_y_intersection;

    while (!is_wall(x, y, data))
    {
        x += data->raycas->x_step;
        y += data->raycas->y_step;
    }

    data->raycas->end_x_vertical = x;
    data->raycas->end_y_vertical = y;
    data->raycas->distance_vertical = sqrt(pow(x - data->player->player_x, 2) + pow(y - data->player->player_y, 2));
}

void player_facing(t_data *data)
{
    data->raycas->is_ray_facing_down = (data->raycas->ray_angle > 0 && data->raycas->ray_angle < M_PI);
    data->raycas->is_ray_facing_up = !data->raycas->is_ray_facing_down;
    data->raycas->is_ray_facing_right = (data->raycas->ray_angle < 0.5 * M_PI || data->raycas->ray_angle > 1.5 * M_PI);
    data->raycas->is_ray_facing_left = !data->raycas->is_ray_facing_right;
}

void cast_ray(t_data *data)
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

void cast_rays(t_data *data)
{
    float ray_angle;
    float angle_step;
    float start_angle;
    int ray;

    angle_step = FOV_ANGLE / NUM_RAYS;
    start_angle = data->player->angle - (FOV_ANGLE / 2);
    normalize_angle(&start_angle);

    ray = 0;
    while (ray < NUM_RAYS)
    {
        ray_angle = start_angle + (angle_step * ray);
        normalize_angle(&ray_angle);
        data->raycas->ray_angle = ray_angle;
        cast_ray(data);

        draw_line(data->player->player_x, data->player->player_y, data->raycas->wall_hit_x, data->raycas->wall_hit_y, data);
        ray++;
    }
}
