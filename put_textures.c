/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 10:29:48 by oel-moue          #+#    #+#             */
/*   Updated: 2024/12/24 16:00:58 by oel-moue         ###   ########.fr       */
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

    // Ensure texture coordinates are within bounds
    tex_x = tex_x & 63;  // Same as tex_x % 64, but faster
    tex_y = tex_y & 63;  // Same as tex_y % 64, but faster
    
    pixel = texture->addr + (tex_y * texture->line_length + tex_x * (texture->bits_per_pixel / 8));
    color = *(unsigned int*)pixel;
    
    return (color);
}

void draw_textured_wall(t_data *data, int ray_id, int wall_start, int wall_end)
{
    t_texture *texture;
    t_e_texture side;
    double wall_height;
    int tex_x;
    double step;
    double tex_pos;

    // Determine which wall texture to use
    side = determine_wall_side(data, ray_id);
    texture = &data->texture[side];

    // Get the exact hit point on the wall
    double wall_hit_x = data->raycas->ray[ray_id].wall_hit_x;
    double wall_hit_y = data->raycas->ray[ray_id].wall_hit_y;

    // Determine which coordinate to use based on wall side
    if (side == NORTH || side == SOUTH)
        tex_x = (int)(wall_hit_x * TEXTURE_SIZE) % TEXTURE_SIZE;
    else
        tex_x = (int)(wall_hit_y * TEXTURE_SIZE) % TEXTURE_SIZE;

    // Ensure tex_x is positive
    if (tex_x < 0)
        tex_x += TEXTURE_SIZE;

    // Calculate height of wall slice
    wall_height = wall_end - wall_start;

    // Calculate step and initial texture position
    step = (double)TEXTURE_SIZE / wall_height;
    tex_pos = (wall_start - data->img->height / 2 + wall_height / 2) * step;

    // Draw each pixel row of the wall slice
    for (int y = wall_start; y < wall_end; y++)
    {
        int tex_y = (int)tex_pos & (TEXTURE_SIZE - 1);
        tex_pos += step;

        unsigned int color = get_texture_color(texture, tex_x, tex_y);
        my_mlx_pixel_put(data->img, ray_id, y, color);
    }
}
