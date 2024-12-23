/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 10:29:48 by oel-moue          #+#    #+#             */
/*   Updated: 2024/12/23 10:34:47 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

unsigned int get_texture_color(t_texture *texture, int tex_x, int tex_y)
{
    char *pixel;
    unsigned int color;

    // Boundary checks
    if (tex_x < 0)
        tex_x = 0;
    if (tex_x >= texture->width)
        tex_x = texture->width - 1;
    if (tex_y < 0)
        tex_y = 0;
    if (tex_y >= texture->height)
        tex_y = texture->height - 1;

    pixel = texture->addr + (tex_y * texture->line_length + tex_x * (texture->bits_per_pixel / 8));
    color = *(unsigned int*)pixel;
    return color;
}

// Draw a textured wall slice
void draw_textured_wall(t_data *data, int ray_id, int wall_start, int wall_end)
{
    t_e_texture side;
    t_texture *texture;
    unsigned int color;
    double wall_x;
    int tex_x;
    int tex_y;
    double step;
    double tex_pos;

    // Determine which side the wall is on
    side = determine_wall_side(data, ray_id);
    texture = &data->texture[side];

    // Calculate the exact position where the wall was hit
    if (side == NORTH || side == SOUTH)
        wall_x = data->raycas->ray[ray_id].wall_hit_x;
    else
        wall_x = data->raycas->ray[ray_id].wall_hit_y;

    // Get the fractional part of wall_x to map to texture
    wall_x -= floor(wall_x / SQUAR_SIZE) * SQUAR_SIZE;

    // Calculate texture x-coordinate
    tex_x = (int)(wall_x * (double)texture->width / SQUAR_SIZE);
    if ((side == SOUTH && data->raycas->ray[ray_id].is_ray_facing_down) ||
        (side == EAST && data->raycas->ray[ray_id].is_ray_facing_right))
        tex_x = texture->width - tex_x - 1;

    // Calculate how much to increase the texture coordinate per screen pixel
    step = (double)texture->height / (double)(wall_end - wall_start);
    tex_pos = 0.0;

    for (int y = wall_start; y <= wall_end; y++)
    {
        tex_y = (int)tex_pos;
        tex_pos += step;
        color = get_texture_color(texture, tex_x, tex_y);
        my_mlx_pixel_put(data->img, ray_id, y, color);
    }
}