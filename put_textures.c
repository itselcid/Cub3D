/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 10:29:48 by oel-moue          #+#    #+#             */
/*   Updated: 2025/01/06 21:08:47 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_e_texture	determine_wall_side(t_data *data, int ray_id)
{
	// If we hit a horizontal wall (y intersection)
	if (data->raycas->ray[ray_id].horizontal_distance < data->raycas->ray[ray_id].vertical_distance)
	{
		if (data->raycas->ray[ray_id].is_ray_facing_up)
			return (NORTH); // Hit north-facing wall
		return (SOUTH);     // Hit south-facing wall
	}
	// If we hit a vertical wall (x intersection)
	else
	{
		if (data->raycas->ray[ray_id].is_ray_facing_right)
			return (EAST); // Hit east-facing wall
		return (WEST);     // Hit west-facing wall
	}
}

unsigned int	get_texture_color(t_texture *texture, int tex_x, int tex_y, t_data *data)
{
	char			*pixel;
	unsigned int	color;

	// Ensure texture coordinates are within bounds using modulus for more flexibility
	tex_x = tex_x % data->size_textures;
	tex_y = tex_y % data->size_textures;
	// Calculate pixel address in the texture array
	pixel = texture->addr + (tex_y * texture->line_length + tex_x
			* (texture->bits_per_pixel / 8));
	color = *(unsigned int *)pixel;
	return (color);
}

void draw_textured_wall(t_data *game, int x, float wall_height, int ray_index)
{
    int wall_top = (WINDOW_HEIGHT - (int)wall_height) / 2;
    if (wall_top < 0)
        wall_top = 0;

    int wall_bottom = (WINDOW_HEIGHT + (int)wall_height) / 2;
    if (wall_bottom >= WINDOW_HEIGHT)
        wall_bottom = WINDOW_HEIGHT - 1;

    // Determine which texture to use and calculate the wall hit position
    t_e_texture side = determine_wall_side(game, ray_index);
    // Normalize wall_x to the texture's range
    double wall_x;
if (side == NORTH || side == SOUTH) {
    wall_x = game->raycas->ray[ray_index].wall_hit_x;
} else {
    wall_x = game->raycas->ray[ray_index].wall_hit_y;
}
    wall_x = fmod(wall_x, game->size_textures);
    if (wall_x < 0)
        wall_x += game->size_textures;

    int tex_x = (int)(wall_x * game->texture[side].width / game->size_textures);
    // Clamp tex_x to avoid accessing out-of-bounds pixels
    if (tex_x >= game->texture[side].width)
        tex_x = game->texture[side].width - 1;

    // Calculate texture mapping parameters
    double step = (double)game->texture[side].height / wall_height;
    double tex_pos = (wall_top - WINDOW_HEIGHT / 2.0 + wall_height / 2.0) * step;

    // Draw the wall slice
    for (int y = wall_top; y < wall_bottom; y++)
    {
        int tex_y = (int)tex_pos & (game->texture[side].height - 1);
        unsigned int color  = get_texture_color(&game->texture[side],tex_x,tex_y, game );

        my_mlx_pixel_put(game->img, x, y, color);
        tex_pos += step;
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