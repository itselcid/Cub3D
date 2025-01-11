/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:24:52 by oel-moue          #+#    #+#             */
/*   Updated: 2025/01/11 15:07:25 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	player_facing(t_data *data, int ray_id)
{
	float	ray_angle;

	ray_angle = data->raycas->ray[ray_id].ray_angle;
	data->raycas->ray[ray_id].down = ray_angle > 0 && ray_angle < M_PI;
	data->raycas->ray[ray_id].up = !data->raycas->ray[ray_id].down;
	data->raycas->ray[ray_id].right = ray_angle < 0.5 * M_PI || ray_angle > 1.5
		* M_PI;
	data->raycas->ray[ray_id].left = !data->raycas->ray[ray_id].right;
}

void	cast_ray(t_data *data, int ray_id)
{
	double	h_distance;
	double	v_distance;

	player_facing(data, ray_id);
	h_distance = distance_horizontal(data, ray_id);
	v_distance = distance_vertical(data, ray_id);
	if (h_distance < v_distance)
	{
		data->raycas->ray[ray_id].wall_x = data->raycas->ray[ray_id].end_x_h;
		data->raycas->ray[ray_id].wall_y = data->raycas->ray[ray_id].end_y_h;
		data->raycas->ray[ray_id].ray_distance = h_distance;
	}
	else
	{
		data->raycas->ray[ray_id].wall_x = data->raycas->ray[ray_id].end_x_v;
		data->raycas->ray[ray_id].wall_y = data->raycas->ray[ray_id].end_y_v;
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
		projection_wall(data, ray_id);
		ray_id++;
	}
}
