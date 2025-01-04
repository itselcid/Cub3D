/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 10:29:48 by oel-moue          #+#    #+#             */
/*   Updated: 2025/01/04 12:50:07 by oel-moue         ###   ########.fr       */
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

void draw_textured_wall(t_data *data, int ray_id, double wall_top, double wall_bottom, double wall_height)
{
    int x;
    int y;
    unsigned int color;
    t_e_texture side;
    t_texture *texture;

    side = determine_wall_side(data, ray_id);
    texture = &data->texture[side];

    if (data->raycas->ray[ray_id].horizontal_distance < data->raycas->ray[ray_id].vertical_distance)
        x = (int)(data->raycas->ray[ray_id].wall_hit_x) % data->size_textures;
    else
        x = (int)(data->raycas->ray[ray_id].wall_hit_y) % data->size_textures;

    if (x < 0)
        x = 0;
    else if (x >= data->size_textures)
        x = data->size_textures - 1;

    for (int current_y = (int)wall_top; current_y < (int)wall_bottom; current_y++)
    {
        double relative_pos = ((double)(current_y) - (data->img->height / 2.0) + (wall_height / 2.0)) / wall_height;

        if (relative_pos < 0.0)
            relative_pos = 0.0;
        else if (relative_pos > 1.0)
            relative_pos = 1.0;

        y = (int)(relative_pos * (double)data->size_textures);

        if (y < 0)
            y = 0;
        else if (y >= data->size_textures)
            y = data->size_textures - 1;

        color = get_texture_color(texture, x, y, data);

        my_mlx_pixel_put(data->img, ray_id, current_y, color);
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