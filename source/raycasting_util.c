/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_util.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 14:34:03 by oel-moue          #+#    #+#             */
/*   Updated: 2025/01/10 16:33:08 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

double	calcule_first_intersection_with_x(t_data *data, int ray_id,
		double player_x, double player_y)
{
	double	x;

	if (data->raycas->ray[ray_id].up)
	{
		data->raycas->ray[ray_id].y_first_point = floor(player_y
				/ data->size_textures) * data->size_textures - 0.0001;
		data->raycas->ray[ray_id].y_step = -data->size_textures;
	}
	else
	{
		data->raycas->ray[ray_id].y_first_point = floor(player_y
				/ data->size_textures) * data->size_textures
			+ data->size_textures;
		data->raycas->ray[ray_id].y_step = data->size_textures;
	}
	x = player_x + (data->raycas->ray[ray_id].y_first_point - player_y)
		/ tan(data->raycas->ray[ray_id].ray_angle);
	data->raycas->ray[ray_id].x_step = data->raycas->ray[ray_id].y_step
		/ tan(data->raycas->ray[ray_id].ray_angle);
	if ((data->raycas->ray[ray_id].left && data->raycas->ray[ray_id].x_step > 0)
		|| (data->raycas->ray[ray_id].right
			&& data->raycas->ray[ray_id].x_step < 0))
		data->raycas->ray[ray_id].x_step = -data->raycas->ray[ray_id].x_step;
	return (x);
}

double	calcule_first_intersection_with_y(t_data *data, int ray_id,
		double player_x, double player_y)
{
	double	y;

	if (data->raycas->ray[ray_id].left)
	{
		data->raycas->ray[ray_id].x_first_point = floor(player_x
				/ data->size_textures) * data->size_textures - 0.0001;
		data->raycas->ray[ray_id].x_step = -data->size_textures;
	}
	else
	{
		data->raycas->ray[ray_id].x_first_point = floor(player_x
				/ data->size_textures) * data->size_textures
			+ data->size_textures;
		data->raycas->ray[ray_id].x_step = data->size_textures;
	}
	y = player_y + (data->raycas->ray[ray_id].x_first_point - player_x)
		* tan(data->raycas->ray[ray_id].ray_angle);
	data->raycas->ray[ray_id].y_step = data->raycas->ray[ray_id].x_step
		* tan(data->raycas->ray[ray_id].ray_angle);
	if ((data->raycas->ray[ray_id].up && data->raycas->ray[ray_id].y_step > 0)
		|| (data->raycas->ray[ray_id].down
			&& data->raycas->ray[ray_id].y_step < 0))
		data->raycas->ray[ray_id].y_step = -data->raycas->ray[ray_id].y_step;
	return (y);
}

int	is_wall(double x, double y, t_data *data)
{
	int	map_x;
	int	map_y;

	map_x = (int)(x / data->size_textures);
	map_y = (int)(y / data->size_textures);
	if (map_x < 0 || map_x >= data->w || map_y < 0 || map_y >= data->h)
		return (1);
	if (data->input->map_data[map_y][map_x] == '1')
		return (1);
	return (0);
}

double	distance_horizontal(t_data *data, int ray_id)
{
	double	player_x;
	double	player_y;
	double	x;
	double	y;

	player_x = data->player->player_x * data->size_textures;
	player_y = data->player->player_y * data->size_textures;
	x = calcule_first_intersection_with_x(data, ray_id, player_x, player_y);
	y = data->raycas->ray[ray_id].y_first_point;
	while (x >= 0 && x < (data->input->width * data->size_textures) && y >= 0
		&& y < (data->input->height * data->size_textures))
	{
		if (is_wall(x, y, data))
		{
			break ;
		}
		x += data->raycas->ray[ray_id].x_step;
		y += data->raycas->ray[ray_id].y_step;
	}
	data->raycas->ray[ray_id].end_x_h = x;
	data->raycas->ray[ray_id].end_y_h = y;
	data->raycas->ray[ray_id].horizontal_distance = sqrt(pow(x - player_x, 2)
			+ pow(y - player_y, 2));
	return (data->raycas->ray[ray_id].horizontal_distance);
}

double	distance_vertical(t_data *data, int ray_id)
{
	double	player_x;
	double	player_y;
	double	x;
	double	y;

	player_x = data->player->player_x * data->size_textures;
	player_y = data->player->player_y * data->size_textures;
	y = calcule_first_intersection_with_y(data, ray_id, player_x, player_y);
	x = data->raycas->ray[ray_id].x_first_point;
	while (x >= 0 && x < (data->input->width * data->size_textures) && y >= 0
		&& y < (data->input->height * data->size_textures))
	{
		if (is_wall(x, y, data))
		{
			break ;
		}
		x += data->raycas->ray[ray_id].x_step;
		y += data->raycas->ray[ray_id].y_step;
	}
	data->raycas->ray[ray_id].end_x_v = x;
	data->raycas->ray[ray_id].end_y_v = y;
	data->raycas->ray[ray_id].vertical_distance = sqrt(pow(x - player_x, 2)
			+ pow(y - player_y, 2));
	return (data->raycas->ray[ray_id].vertical_distance);
}
