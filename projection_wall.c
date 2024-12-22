/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection_wall.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 13:49:36 by oel-moue          #+#    #+#             */
/*   Updated: 2024/12/22 17:04:12 by oel-moue         ###   ########.fr       */
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

t_e_texture determine_wall_side(t_data *data, int ray_id)
{ 
    // If we hit a horizontal wall (y intersection)
    if (data->raycas->ray[ray_id].horizontal_distance < data->raycas->ray[ray_id].vertical_distance)
    {
        if (data->raycas->ray[ray_id].is_ray_facing_up)
            return NORTH;  // Hit north-facing wall
        return SOUTH;     // Hit south-facing wall
    }
    // If we hit a vertical wall (x intersection)
    else
    {
        if (data->raycas->ray[ray_id].is_ray_facing_right)
            return EAST;   // Hit east-facing wall
        return WEST;      // Hit west-facing wall
    }
}


void draw_colored_wall(t_data *data, int ray_id, int wall_start, int wall_end) {
    t_e_texture side = determine_wall_side(data, ray_id);
    int color;

    // Simple color assignment - same color for all walls of the same orientation
    if (side == NORTH)
        color = 0x00FF00;      // Green for all North walls
    else if (side == SOUTH)
        color = 0xFF0000;      // Red for all South walls
    else if (side == EAST)
        color = 0x0000FF;      // Blue for all East walls
    else // WEST
        color = 0xFFFF00;      // Yellow for all West walls

    // Draw the vertical line with the assigned color
    int y = wall_start;
    while (y <= wall_end) {
        my_mlx_pixel_put(data->img, ray_id, y, color);
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
        // draw the wall for the N / S / E / W
        draw_colored_wall(data, ray_id, wall_top, wall_bottom);
        draw_vertical_line(data, ray_id, wall_bottom + 1, data->img->height - 1, 0x8B4513);
        ray_id++;
    }
}
