/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:24:52 by oel-moue          #+#    #+#             */
/*   Updated: 2025/01/06 20:57:07 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	calcule_first_intersection_with_x(t_data *data, int ray_id)
{
	double	first_intersection_by_x;
	double	player_x;
	double	player_y;

	player_x = data->player->player_x * data->size_textures;
	player_y = data->player->player_y * data->size_textures;
	if (data->raycas->ray[ray_id].is_ray_facing_up)
	{
		data->raycas->ray[ray_id].y_first_point_with_x_intersection = floor(player_y
				/ data->size_textures) * data->size_textures - 0.0001;
		data->raycas->ray[ray_id].y_step = -data->size_textures;
	}
	else
	{
		data->raycas->ray[ray_id].y_first_point_with_x_intersection = floor(player_y
				/ data->size_textures) * data->size_textures + data->size_textures;
		data->raycas->ray[ray_id].y_step = data->size_textures;
	}
	first_intersection_by_x = player_x
		+ (data->raycas->ray[ray_id].y_first_point_with_x_intersection - player_y)
		/ tan(data->raycas->ray[ray_id].ray_angle);
	data->raycas->ray[ray_id].x_step = data->raycas->ray[ray_id].y_step / tan(data->raycas->ray[ray_id].ray_angle);
	if ((data->raycas->ray[ray_id].is_ray_facing_left && data->raycas->ray[ray_id].x_step > 0)
		|| (data->raycas->ray[ray_id].is_ray_facing_right && data->raycas->ray[ray_id].x_step < 0))
	{
		data->raycas->ray[ray_id].x_step = -data->raycas->ray[ray_id].x_step;
	}
	return (first_intersection_by_x);
}

double	calcule_first_intersection_with_y(t_data *data , int ray_id)
{
	double	first_intersection_by_y;
	double	player_x;
	double	player_y;

	player_x = data->player->player_x * data->size_textures;
	player_y = data->player->player_y * data->size_textures;
	if (data->raycas->ray[ray_id].is_ray_facing_left)
	{
		data->raycas->ray[ray_id].x_first_point_with_y_intersection = floor(player_x
				/ data->size_textures) * data->size_textures - 0.0001;
		data->raycas->ray[ray_id].x_step = -data->size_textures;
	}
	else
	{
		data->raycas->ray[ray_id].x_first_point_with_y_intersection = floor(player_x
				/ data->size_textures) * data->size_textures + data->size_textures;
		data->raycas->ray[ray_id].x_step = data->size_textures;
	}
	first_intersection_by_y = player_y
		+ (data->raycas->ray[ray_id].x_first_point_with_y_intersection - player_x)
		* tan(data->raycas->ray[ray_id].ray_angle);
	data->raycas->ray[ray_id].y_step = data->raycas->ray[ray_id].x_step * tan(data->raycas->ray[ray_id].ray_angle);
	if ((data->raycas->ray[ray_id].is_ray_facing_up && data->raycas->ray[ray_id].y_step > 0)
		|| (data->raycas->ray[ray_id].is_ray_facing_down && data->raycas->ray[ray_id].y_step < 0))
	{
		data->raycas->ray[ray_id].y_step = -data->raycas->ray[ray_id].y_step;
	}
	return (first_intersection_by_y);
}

int	is_wall(double x, double y, t_data *data)
{
	int	map_x;
	int	map_y;
	// We're already working with pixel coordinates, so adjust the division
	map_x = floor(x) / data->size_textures;
	map_y = floor(y) / data->size_textures;
	if (map_x < 0 || map_x >= data->w || map_y < 0 || map_y >= data->h)
		return (1);
	if (data->input->map_data[map_y][map_x] == '1')
		return (1);
	return (0);
}

double	distance_horizontal(t_data *data , int ray_id)
{
	double	player_x;
	double	player_y;

	double x, y;
	player_x = data->player->player_x * data->size_textures;
	player_y = data->player->player_y * data->size_textures;
	x = calcule_first_intersection_with_x(data, ray_id);
	y = data->raycas->ray[ray_id].y_first_point_with_x_intersection;
	while (x >= 0 && x < (data->input->width * data->size_textures ) && y >= 0 && y < (data->input->height * data->size_textures))
	{
		if (is_wall(x, y, data))
		{
			break ;
		}
		x += data->raycas->ray[ray_id].x_step;
		y += data->raycas->ray[ray_id].y_step;
	}
	data->raycas->ray[ray_id].end_x_horizontal = x;
	data->raycas->ray[ray_id].end_y_horizontal = y;
	data->raycas->ray[ray_id].horizontal_distance = sqrt(pow(x - player_x, 2) + pow(y
				- player_y, 2));
	return (data->raycas->ray[ray_id].horizontal_distance);
}

double	distance_vertical(t_data *data , int ray_id)
{
	double	player_x;
	double	player_y;

	double x, y;
	player_x = data->player->player_x * data->size_textures;
	player_y = data->player->player_y * data->size_textures;
	y = calcule_first_intersection_with_y(data, ray_id);
	x = data->raycas->ray[ray_id].x_first_point_with_y_intersection;
	while (x >= 0 && x < (data->input->width * data->size_textures ) && y >= 0 && y < (data->input->height * data->size_textures))
	{
		if (is_wall(x, y, data))
		{
			break ;
		}
		x += data->raycas->ray[ray_id].x_step;
		y += data->raycas->ray[ray_id].y_step;
	}
	data->raycas->ray[ray_id].end_x_vertical = x;
	data->raycas->ray[ray_id].end_y_vertical = y;
	data->raycas->ray[ray_id].vertical_distance = sqrt(pow(x - player_x, 2) + pow(y
				- player_y, 2));
	return (data->raycas->ray[ray_id].vertical_distance);
}

void	player_facing(t_data *data , int ray_id)
{
	data->raycas->ray[ray_id].is_ray_facing_down = data->raycas->ray[ray_id].ray_angle > 0
		&& data->raycas->ray[ray_id].ray_angle < M_PI;
	data->raycas->ray[ray_id].is_ray_facing_up = !data->raycas->ray[ray_id].is_ray_facing_down;
	data->raycas->ray[ray_id].is_ray_facing_right = data->raycas->ray[ray_id].ray_angle < 0.5 * M_PI
		|| data->raycas->ray[ray_id].ray_angle > 1.5 * M_PI;
	data->raycas->ray[ray_id].is_ray_facing_left = !data->raycas->ray[ray_id].is_ray_facing_right;
}

void	draw_ray(t_data *data, int ray_id)
{
	double	x_end;
	double	y_end;
	double	x0;
	double	y0;

	x0 = data->player->player_x * data->size_textures;
	y0 = data->player->player_y * data->size_textures;
	x_end = data->raycas->ray[ray_id].wall_hit_x;
	y_end = data->raycas->ray[ray_id].wall_hit_y;
	ft_draw_line(data, x0, y0, x_end, y_end);
}

void	cast_ray(t_data *data , int ray_id)
{
	double h_distance, v_distance;                                                                                                                         
	player_facing(data, ray_id);
	h_distance = distance_horizontal(data, ray_id);
	v_distance = distance_vertical(data , ray_id);
	if (h_distance < v_distance)
	{
		data->raycas->ray[ray_id].wall_hit_x = data->raycas->ray[ray_id].end_x_horizontal;
		data->raycas->ray[ray_id].wall_hit_y = data->raycas->ray[ray_id].end_y_horizontal;
		data->raycas->ray[ray_id].ray_distance = h_distance;
		//draw_ray(data, ray_id);
	}
	else
	{
		data->raycas->ray[ray_id].wall_hit_x = data->raycas->ray[ray_id].end_x_vertical;
		data->raycas->ray[ray_id].wall_hit_y = data->raycas->ray[ray_id].end_y_vertical;
		data->raycas->ray[ray_id].ray_distance = v_distance;
		//draw_ray(data, ray_id);
	}
}

void	cast_rays(t_data *data)
{
	double	ray_angle;
	int		ray_id;
	double	angle_step;
	double	start_angle;

	//data->raycas->nbr_ray = data->img->width;
	angle_step = FOV_ANGLE / data->raycas->nbr_ray;
	start_angle = data->player->angle - (FOV_ANGLE / 2);
	int nbr_ray = data->raycas->nbr_ray;
	ray_id = 0;
	while (ray_id < nbr_ray)
	{
		ray_angle = start_angle + ray_id * angle_step;
		normalize_angle(&ray_angle);
		data->raycas->ray[ray_id].ray_angle = ray_angle;
		cast_ray(data, ray_id);
		ray_id++;
	}
}
