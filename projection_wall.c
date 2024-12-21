/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection_wall.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 13:49:36 by oel-moue          #+#    #+#             */
/*   Updated: 2024/12/21 21:20:28 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void draw_vertical_line(t_data *data, int x, int start, int end, int color)
{
    // Clamp the start and end points to stay within screen bounds
    start = fmax(0, start);
    end = fmin(data->img->height - 1, end);
    
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
    double distance_to_plane;
    //double corrected_distance;
    int ray_id;

    ray_id = 0;
    // Calculate the distance to the projection plane once
    distance_to_plane = (data->img->width / 2) / tan(FOV_ANGLE / 2);
    
    while (ray_id < data->raycas->nbr_ray)
    {
        double corrected_distance = data->raycas->ray[ray_id].ray_distance * cos(data->raycas->ray[ray_id].ray_angle - data->player->angle);
        wall_height = (SQUAR_SIZE / corrected_distance) * distance_to_plane;
        int wall_top = (data->img->height / 2) - ((int)wall_height / 2);
        int wall_bottom = (data->img->height / 2) + ((int)wall_height / 2);
        draw_vertical_line(data, ray_id, 0, wall_top - 1, 0x87CEEB);
        draw_vertical_line(data, ray_id, wall_top, wall_bottom, 0x808080);  
        draw_vertical_line(data, ray_id, wall_bottom + 1, data->img->height - 1, 0x8B4513);
        
        ray_id++;
    }
}
