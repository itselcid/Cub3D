/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection_wall.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 13:49:36 by oel-moue          #+#    #+#             */
/*   Updated: 2024/12/21 16:21:28 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void draw_vertical_line(t_data *data, int x, int start, int end, int color)
{
    int y = start;
    while (y <= end)
    {
        my_mlx_pixel_put(data->img, x, y, color);
        y++;
    }
}

void projection_wall(t_data *data)
{
    double wall_height;
    double DistanceToProjectionPlane;
    int ray_id;

    ray_id = 0;
    while (ray_id < data->raycas->nbr_ray)
    {
        DistanceToProjectionPlane = (data->img->width / 2) / tan(FOV_ANGLE / 2);
        wall_height = (SQUAR_SIZE / data->raycas->ray[ray_id].ray_distance) * DistanceToProjectionPlane;

        // Calculate the start and end positions for the vertical line
        int wall_start = (data->img->height / 2) - (wall_height / 2);
        int wall_end = (data->img->height / 2) + (wall_height / 2);
        draw_vertical_line(data, ray_id, wall_start, wall_end, 0x00FF00);
        ray_id++;
    }
}
