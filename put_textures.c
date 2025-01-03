/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 10:29:48 by oel-moue          #+#    #+#             */
/*   Updated: 2025/01/03 16:20:46 by oel-moue         ###   ########.fr       */
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
#include <math.h>  // Ensure math functions are available

// Fix texture coordinate wrapping
unsigned int get_texture_color(t_texture *texture, int tex_x, int tex_y)
{
    char *pixel;
    unsigned int color;

    // Ensure texture coordinates are within bounds using modulus for more flexibility
    tex_x = tex_x % TEXTURE_WIDTH;
    tex_y = tex_y % TEXTURE_HEIGHT;
    
    // Calculate pixel address in the texture array
    pixel = texture->addr + (tex_y * texture->line_length + tex_x * (texture->bits_per_pixel / 8));
    color = *(unsigned int*)pixel;
    
    return color;
}

// Fix in the texture drawing logic
// void draw_textured_wall(t_data *data, int ray_id, int wall_start, int wall_end)
// {
//     t_texture *texture;
//     int tex_x, tex_y;
//     double step;
//     double tex_pos;

//     // Get wall side and corresponding texture
//     t_e_texture side = determine_wall_side(data, ray_id);
//     if (side < 0) {
//         fprintf(stderr, "Invalid wall side: %d\n", side);
//         return;
//     }
//     texture = &data->texture[side];

//     // Calculate texture X coordinate based on wall hit point
//     double wall_x;
//     if (side == NORTH || side == SOUTH) {
//         wall_x = data->raycas->ray[ray_id].wall_hit_x - floor(data->raycas->ray[ray_id].wall_hit_x);
//     } else {
//         wall_x = data->raycas->ray[ray_id].wall_hit_y - floor(data->raycas->ray[ray_id].wall_hit_y);
//     }

//     // Ensure wall_x is always between 0 and 1
//     wall_x = fmod(wall_x, 1.0);

//     tex_x = (int)(wall_x * TEXTURE_WIDTH);
//     if (side == SOUTH || side == WEST) {
//         tex_x = TEXTURE_WIDTH - tex_x - 1;  // Flip texture for certain sides
//     }

//     // Validate tex_x range
//     if (tex_x < 0 || tex_x >= TEXTURE_WIDTH) {
//         fprintf(stderr, "Invalid tex_x value: %d\n", tex_x);
//         return;
//     }

//     // Clamp wall_start and wall_end to screen bounds
//     if (wall_start < 0) wall_start = 0;
//     if (wall_end >= WINDOW_HEIGHT) wall_end = WINDOW_HEIGHT - 1;

//     // Calculate vertical texture step and initial texture position
//     step = (double)TEXTURE_HEIGHT / (wall_end - wall_start);
//     tex_pos = 0;  // Start from the top of the texture for the first pixel

//     // Draw vertical textured line
//     for (int y = wall_start; y < wall_end; y++) {
//         if (y >= 0 && y < WINDOW_HEIGHT) {
//             tex_y = (int)tex_pos % TEXTURE_HEIGHT;  // Ensure tex_y is within texture bounds
//             tex_pos += step;

//             if (tex_y < 0 || tex_y >= TEXTURE_HEIGHT) {
//                 fprintf(stderr, "Invalid tex_y value: %d\n", tex_y);
//                 return;
//             }

//             unsigned int color = get_texture_color(texture, tex_x, tex_y);
//             if (color == 0xFFFFFFFF) {  // Assuming white indicates invalid texture color
//                 fprintf(stderr, "Invalid texture color at tex_x=%d, tex_y=%d\n", tex_x, tex_y);
//                 return;
//             }

//             my_mlx_pixel_put(data->img, ray_id, y, color);
//         }
//     }
// }


void draw_textured_wall(t_data *data, int ray_id, double top , double bottom , int wall_height)
{
    int		x;
    int		y;
    double	color;

    t_e_texture side = determine_wall_side(data, ray_id);
    t_texture *texture = &data->texture[side];
    if(data->raycas->ray[ray_id].horizontal_distance < data->raycas->ray[ray_id].vertical_distance)
        x = (int)data->raycas->ray[ray_id].wall_hit_x % TEXTURE_HEIGHT;
    else 
        x = (int)data->raycas->ray[ray_id].wall_hit_y % TEXTURE_HEIGHT;
    while (top < bottom)
    {
        y = (int)((top - (data->img->height - wall_height / 2) * (texture->height / wall_height)));
        color = get_texture_color(texture, x, y);
        my_mlx_pixel_put(data->img, ray_id, top, color);
        top++;
    }
}

// void	draw_wall(t_win *win, double t_pix, double b_pix, double wall_h)
// {
// 	int		x;
// 	int		y;
// 	double	color;

// 	if (win->ray.flag)
// 		x = (int)win->hit_x % TEXTURE_H;
// 	else
// 		x = (int)win->hit_y % TEXTURE_H;
// 	while (t_pix < b_pix)
// 	{
// 		y = (t_pix - ((HEIGHT - wall_h) / 2)) * (TEXTURE_H
// 				/ wall_h);
// 		color = get_pixel_img(win->texture[direction(win)], x, y);
// 		my_mlx_pixel_put1(win->frame, win->ray.ray, t_pix, color);
// 		t_pix++;
// 	}
// }