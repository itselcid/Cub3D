/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: el_cid <el_cid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 10:29:48 by oel-moue          #+#    #+#             */
/*   Updated: 2025/01/11 16:25:26 by el_cid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_e_texture	determine_wall_side(t_data *data, int ray_id)
{
	double	d_horizantal;
	double	d_vertical;

	d_horizantal = data->raycas->ray[ray_id].horizontal_distance;
	d_vertical = data->raycas->ray[ray_id].vertical_distance;
	if (d_horizantal < d_vertical)
	{
		if (data->raycas->ray[ray_id].up)
			return (NORTH);
		return (SOUTH);
	}
	else
	{
		if (data->raycas->ray[ray_id].right)
			return (EAST);
		return (WEST);
	}
}

unsigned int	get_texture_color(t_texture *texture, double tex_x,
		double tex_y, t_data *data)
{
	int		x;
	int		y;
	char	*pixel;

	// Use precise floating point texture coordinates
	x = (int)(tex_x * (texture->width / (double)data->size_textures));
	y = (int)(tex_y * (texture->height / (double)data->size_textures));
	// Ensure coordinates are within bounds
	x = x < 0 ? 0 : (x >= texture->width ? texture->width - 1 : x);
	y = y < 0 ? 0 : (y >= texture->height ? texture->height - 1 : y);
	pixel = texture->addr + (y * texture->line_length + x
			* (texture->bits_per_pixel / 8));
	return (*(unsigned int *)pixel);
}

void	var_use_in_image(t_var_for_textures *var, float wall_height,
		int ray_index, t_data *game)
{
	// Calculate precise wall boundaries
	var->wall_top = (WINDOW_HEIGHT - wall_height) / 2.0;
	var->wall_bottom = (WINDOW_HEIGHT + wall_height) / 2.0;
	// Determine wall side and texture x-coordinate
	var->side = determine_wall_side(game, ray_index);
	var->wall_x = (var->side == NORTH
			|| var->side == SOUTH) ? game->raycas->ray[ray_index].wall_x : game->raycas->ray[ray_index].wall_y;
	// Precise texture coordinate calculation
	var->wall_x = fmod(var->wall_x, game->size_textures);
	if (var->wall_x < 0)
		var->wall_x += game->size_textures;
	// Calculate texture step size
	var->step = game->size_textures / wall_height;
	var->tex_pos = (var->wall_top - WINDOW_HEIGHT / 2.0 + wall_height / 2.0)
		* var->step;
}

void	draw_textured_wall(t_data *game, int x, float wall_height,
		int ray_index)
{
	t_var_for_textures	var;
	int					y;
	int					start_y;
	int					end_y;
	double				tex_y;
	unsigned int		color;

	var_use_in_image(&var, wall_height, ray_index, game);
	// Ensure wall boundaries are within screen
	start_y = fmax(0, var.wall_top);
	end_y = fmin(WINDOW_HEIGHT - 1, var.wall_bottom);
	// Adjust texture position for clipped walls
	if (var.wall_top < 0)
		var.tex_pos = -var.wall_top * var.step;
	for (y = start_y; y <= end_y; y++)
	{
		// Calculate precise texture coordinates
		tex_y = var.tex_pos;
		// Get color using precise coordinates
		color = get_texture_color(&game->texture[var.side], var.wall_x, tex_y,
				game);
		my_mlx_pixel_put(game->img, x, y, color);
		var.tex_pos += var.step;
	}
}
