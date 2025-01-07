/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:24:52 by oel-moue          #+#    #+#             */
/*   Updated: 2025/01/07 14:37:29 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	player_facing(t_data *data, int ray_id)
{
	data->raycas->ray[ray_id].is_ray_facing_down = data->raycas->ray[ray_id].ray_angle > 0
		&& data->raycas->ray[ray_id].ray_angle < M_PI;
	data->raycas->ray[ray_id].is_ray_facing_up = !data->raycas->ray[ray_id].is_ray_facing_down;
	data->raycas->ray[ray_id].is_ray_facing_right = data->raycas->ray[ray_id].ray_angle < 0.5
		* M_PI || data->raycas->ray[ray_id].ray_angle > 1.5 * M_PI;
	data->raycas->ray[ray_id].is_ray_facing_left = !data->raycas->ray[ray_id].is_ray_facing_right;
}

void	cast_ray(t_data *data, int ray_id)
{
	double h_distance, v_distance;
	player_facing(data, ray_id);
	h_distance = distance_horizontal(data, ray_id);
	v_distance = distance_vertical(data, ray_id);
	if (h_distance < v_distance)
	{
		data->raycas->ray[ray_id].wall_hit_x = data->raycas->ray[ray_id].end_x_horizontal;
		data->raycas->ray[ray_id].wall_hit_y = data->raycas->ray[ray_id].end_y_horizontal;
		data->raycas->ray[ray_id].ray_distance = h_distance;
	}
	else
	{
		data->raycas->ray[ray_id].wall_hit_x = data->raycas->ray[ray_id].end_x_vertical;
		data->raycas->ray[ray_id].wall_hit_y = data->raycas->ray[ray_id].end_y_vertical;
		data->raycas->ray[ray_id].ray_distance = v_distance;
	}
}

void	cast_rays(t_data *data)
{
	double	ray_angle;
	int		ray_id;
	double	angle_step;
	double	start_angle;
	int		nbr_ray;

	angle_step = FOV_ANGLE / data->raycas->nbr_ray;
	start_angle = data->player->angle - (FOV_ANGLE / 2);
	nbr_ray = data->raycas->nbr_ray;
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
