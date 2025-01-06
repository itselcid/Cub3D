/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection_wall.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 13:49:36 by oel-moue          #+#    #+#             */
/*   Updated: 2025/01/06 21:43:14 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_vertical_line(t_data *data, int x, int start, int end, int color)
{
	int	y;

	// Clamp the start and end points to stay within screen bounds
	start = fmax(0, start);
	end = fmin(data->img->height - 1, end);
	y = start;
	while (y <= end)
	{
		my_mlx_pixel_put(data->img, x, y, color);
		y++;
	}
}

void	draw_colored_wall(t_data *data, int ray_id, int wall_top,
		int wall_bottom)
{
	t_e_texture	side;

	side = determine_wall_side(data, ray_id);
	if (side == NORTH)
		draw_vertical_line(data, ray_id, wall_top, wall_bottom, 0x00FF00);
	else if (side == SOUTH)
		draw_vertical_line(data, ray_id, wall_top, wall_bottom, 0xFF0000);
	else if (side == EAST)
		draw_vertical_line(data, ray_id, wall_top, wall_bottom, 0x0000FF);
	else if (side == WEST)
		draw_vertical_line(data, ray_id, wall_top, wall_bottom, 0xFFFF00);
}

int	rgb_to_int(int *color)
{
	return ((color[0] << 16) | (color[1] << 8) | color[2]);
}

void	draw_texture_sky_floor(t_data *data, int ray_id,
		double corrected_distance)
{
	double	wall_height;
	double	wall_top;
	double	wall_bottom;

	wall_height = (data->size_textures / corrected_distance)
		* PROJECTION_PLANE_DISTANCE;
	wall_top = (data->img->height / 2) - ((int)wall_height / 2);
	wall_bottom = (data->img->height / 2) + ((int)wall_height / 2);
	if (wall_top < 0)
		wall_top = 0;
	if (wall_bottom >= data->img->height)
		wall_bottom = data->img->height - 1;
	draw_vertical_line(data, ray_id, 0, wall_top - 1,
		rgb_to_int(data->input->sky_color));
	draw_textured_wall(data, ray_id, wall_height, ray_id);
	draw_vertical_line(data, ray_id, wall_bottom + 1, data->img->height - 1,
		rgb_to_int(data->input->floor_color));
}
void	projection_wall(t_data *data)
{
	int		ray_id;
	double	angle_diff;
	double	corrected_distance;
	ray_id = 0;
	while (ray_id < data->raycas->nbr_ray)
	{
		angle_diff = data->raycas->ray[ray_id].ray_angle - data->player->angle;
		normalize_angle(&angle_diff);
		corrected_distance = data->raycas->ray[ray_id].ray_distance
			* cos(angle_diff);
		if (corrected_distance <= 0.0)
			corrected_distance = 0.1;
		draw_texture_sky_floor(data, ray_id, corrected_distance);
		ray_id++;
	}
}
