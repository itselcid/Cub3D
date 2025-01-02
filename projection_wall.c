/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection_wall.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 13:49:36 by oel-moue          #+#    #+#             */
/*   Updated: 2025/01/02 15:52:10 by oel-moue         ###   ########.fr       */
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

// void draw_colored_wall(t_data *data, int ray_id, int wall_top, int wall_bottom)
// {
//     t_e_texture side;
//     side = determine_wall_side(data, ray_id);
//     if (side == NORTH)
//         draw_vertical_line(data, ray_id, wall_top, wall_bottom, 0x00FF00);
//     else if (side == SOUTH)
//         draw_vertical_line(data, ray_id, wall_top, wall_bottom, 0xFF0000);
//     else if (side == EAST)
//         draw_vertical_line(data, ray_id, wall_top, wall_bottom, 0x0000FF);
//     else if (side == WEST)
//         draw_vertical_line(data, ray_id, wall_top, wall_bottom, 0xFFFF00);
// }

// void draw_textured_wall(t_data *game, int x, float wall_height, int ray_index)
// {
//     int wall_top = (game->window_height - wall_height) / 2;
//     if (wall_top < 0)
//         wall_top = 0;
//     int wall_bottom = (game->window_height + wall_height) / 2;
//     if (wall_bottom >= game->window_height)
//         wall_bottom = game->window_height - 1;
//     // Draw ceiling
//     draw_ceiling(game, x, wall_top);
//     // Select texture based on wall orientation and direction
//     int texture_index;
//     float wall_x;
//     // Improved precision for texture mapping
//     if (game->rays[ray_index].horizontal_hit_distance < game->rays[ray_index].vertical_hit_distance)
//     {
//         wall_x = game->rays[ray_index].wall_hit_x;
//         texture_index = game->rays[ray_index].is_ray_facing_up ? 0 : 1;
//     }
//     else
//     {
//         wall_x = game->rays[ray_index].wall_hit_y;
//         texture_index = game->rays[ray_index].is_ray_facing_left ? 2 : 3;
//     }
//     // Precise texture coordinate calculation
//     wall_x = wall_x - floor(wall_x / SQUARE_SIZE) * SQUARE_SIZE;
//     float tex_x = wall_x * game->textures[texture_index].width / SQUARE_SIZE;

//     // Prevent texture bleeding
//     tex_x = fmin(tex_x, game->textures[texture_index].width - 0.0001);
//     // Use high-precision step calculation
//     double step = (double)game->textures[texture_index].height / wall_height;
//     double tex_pos = (wall_top - game->window_height / 2.0 + wall_height / 2.0) * step;
//     // Apply distance-based darkness for depth perception
//     float darkness = fmin(1.0, 1.0 / (game->rays[ray_index].distance * 0.0025));
//     // Draw the wall strip with improved texture sampling
//     for (int y = wall_top; y < wall_bottom; y++)
//     {
//         int tex_y = (int)tex_pos & (game->textures[texture_index].height - 1);

//         unsigned int color;
//         get_texture_pixel(&game->textures[texture_index], tex_x, tex_y, &color);
//         // Apply distance-based shading
//         unsigned char r = ((color >> 16) & 0xFF) * darkness;
//         unsigned char g = ((color >> 8) & 0xFF) * darkness;
//         unsigned char b = (color & 0xFF) * darkness;
//         // Combine channels with improved color depth
//         color = (r << 16) | (g << 8) | b;
//         my_mlx_pixel_put(&game->img, x, y, color);
//         tex_pos += step;
//     }
//     // Draw floor
//     draw_floor(game, x, wall_bottom);
// }

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
        
        int color_sky = data->input->sky_color[0] << 16 | data->input->sky_color[1] << 8 | data->input->sky_color[2];
        int color_floor = data->input->floor_color[0] << 16 | data->input->floor_color[1] << 8 | data->input->floor_color[2];
        draw_vertical_line(data, ray_id, 0, wall_top - 1, color_sky);
        // draw the wall for the N / S / E / W
        //draw_colored_wall(data, ray_id, wall_top, wall_bottom);
        //draw_textured_wall(data, ray_id, wall_top, wall_bottom);
        draw_textured_wall1(data, wall_height,ray_id);
        // if (ray_index < WINDOW_WIDTH)
        //     draw_textured_wall(game, ray_index, wall_height, ray_index);if (ray_index < WINDOW_WIDTH)
        //     draw_textured_wall(game, ray_index, wall_height, ray_index);
        //draw_textured_wall1(data, wall_height, corrected_distance, ray_id);
        draw_vertical_line(data, ray_id, wall_bottom + 1, data->img->height - 1, color_floor);
        ray_id++;
    }
}
