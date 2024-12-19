/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:24:52 by oel-moue          #+#    #+#             */
/*   Updated: 2024/12/19 19:37:48 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	calcule_first_intersection_with_x(t_data *data)
{
	double	first_intersection_by_x;

	if (data->raycas->is_ray_facing_down)
	{
		data->raycas->y_first_point_with_x_intersection = floor(data->player->player_y
				/ SQUAR_SIZE) * SQUAR_SIZE + SQUAR_SIZE;
		data->raycas->y_step = SQUAR_SIZE;
	}
	else
	{
		data->raycas->y_first_point_with_x_intersection = floor(data->player->player_y
				/ SQUAR_SIZE) * SQUAR_SIZE;
		data->raycas->y_step = -SQUAR_SIZE;
	}
	first_intersection_by_x = data->player->player_x
		+ (data->raycas->y_first_point_with_x_intersection
			- data->player->player_y) / tan(data->raycas->ray_angle);
	data->raycas->x_step = SQUAR_SIZE / tan(data->raycas->ray_angle);
	if ((data->raycas->is_ray_facing_left && data->raycas->x_step > 0)
		|| (data->raycas->is_ray_facing_right && data->raycas->x_step < 0))
		data->raycas->x_step = -data->raycas->x_step;
	return (first_intersection_by_x);
}

double	calcule_first_intersection_with_y(t_data *data)
{
	double	first_intersection_by_y;

	if (data->raycas->is_ray_facing_right)
	{
		data->raycas->x_first_point_with_y_intersection = floor(data->player->player_x
				/ SQUAR_SIZE) * SQUAR_SIZE + SQUAR_SIZE;
		data->raycas->x_step = SQUAR_SIZE;
	}
	else
	{
		data->raycas->x_first_point_with_y_intersection = floor(data->player->player_x
				/ SQUAR_SIZE) * SQUAR_SIZE;
		data->raycas->x_step = -SQUAR_SIZE;
	}
	first_intersection_by_y = data->player->player_y
		+ (data->raycas->x_first_point_with_y_intersection
			- data->player->player_x) * tan(data->raycas->ray_angle);
	data->raycas->y_step = SQUAR_SIZE * tan(data->raycas->ray_angle);
	if ((data->raycas->is_ray_facing_up && data->raycas->y_step > 0)
		|| (data->raycas->is_ray_facing_down && data->raycas->y_step < 0))
		data->raycas->y_step = -data->raycas->y_step;
	return (first_intersection_by_y);
}

int	is_wall(double x, double y, t_data *data)
{
	int	i;
	int	j;

	i = floor(x / SQUAR_SIZE);
	j = floor(y / SQUAR_SIZE);
	if (i < 0 || i >= data->w || j < 0 || j >= data->h)
		return (1);
	if (data->map[j][i] == '1')
		return (1);
	return (0);
}
double	distance_horizontal(t_data *data)
{
	double x, y;
	x = calcule_first_intersection_with_x(data);
	y = data->raycas->y_first_point_with_x_intersection;
	while (x >= 0 && x < data->img->width && y >= 0 && y < data->img->height)
	{
		if (is_wall(x, y, data))
			break ;
		x += data->raycas->x_step;
		y += data->raycas->y_step;
	}
	// printf("x = %f\n", x);
	data->raycas->end_x_horizontal = x;
	data->raycas->end_y_horizontal = y;
	data->raycas->distance_horizontal = sqrt(pow(x - (data->player->player_x
					* SQUAR_SIZE), 2) + pow(y - (data->player->player_y
					* SQUAR_SIZE), 2));
	return (data->raycas->distance_horizontal);
}

double	distance_vertical(t_data *data)
{
	double x, y;
	x = calcule_first_intersection_with_y(data);
	y = data->raycas->x_first_point_with_y_intersection;
	while (x >= 0 && x < data->img->width && y >= 0 && y < data->img->height)
	{
		if (is_wall(x, y, data))
			break ;
		x += data->raycas->x_step;
		y += data->raycas->y_step;
	}
	data->raycas->end_x_vertical = x;
	data->raycas->end_y_vertical = y;
	data->raycas->distance_vertical = sqrt(pow(x - (data->player->player_x
					* SQUAR_SIZE), 2) + pow(y - (data->player->player_y
					* SQUAR_SIZE), 2));
	return (data->raycas->distance_vertical);
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

void	draw_ray(t_data *data, double distance, double ray_angle)
{
	double	x_end;
	double	y_end;
	double	x0;
	double	y0;

	x0 = data->player->player_x * SQUAR_SIZE;
	y0 = data->player->player_y * SQUAR_SIZE;
	x_end = x0 + cos(ray_angle) * distance;
	y_end = y0 + sin(ray_angle) * distance;
	ft_draw_line(data, x0, y0, x_end, y_end);
}

void	cast_rays(t_data *data)
{
	double	ray_angle;
	int		ray_id;
	int		nbr_ray;
	float	angle_step;
	float	start_angle;

	double h_distance, v_distance;
	nbr_ray = data->img->width;
	angle_step = FOV_ANGLE / nbr_ray;
	start_angle = data->player->angle - (FOV_ANGLE / 2);
	
	ray_id = 0;
	while (ray_id < nbr_ray)
	{
		ray_angle = start_angle + (angle_step * ray_id);
		data->raycas->ray_angle = ray_angle;
		normalize_angle(&data->raycas->ray_angle);
		h_distance = distance_horizontal(data);
		v_distance = distance_vertical(data);
		if (h_distance < v_distance)
		{
			draw_ray(data, h_distance, ray_angle);
		}
		else
			draw_ray(data, v_distance, ray_angle);
		ray_id++;
	}
}
