/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection_wall.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 13:49:36 by oel-moue          #+#    #+#             */
/*   Updated: 2024/12/24 16:21:39 by oel-moue         ###   ########.fr       */
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
void draw_colored_wall(t_data *data, int ray_id, int wall_top, int wall_bottom)
{
    t_e_texture side;
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
        // draw the wall for the N / S / E / W
        draw_colored_wall(data, ray_id, wall_top, wall_bottom);
        //draw_textured_wall(data, ray_id, wall_top, wall_bottom);
        draw_vertical_line(data, ray_id, wall_bottom + 1, data->img->height - 1, 0x8B4513);
        ray_id++;
    }
}
