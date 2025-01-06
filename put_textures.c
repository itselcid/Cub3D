/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 10:29:48 by oel-moue          #+#    #+#             */
/*   Updated: 2025/01/06 22:23:05 by oel-moue         ###   ########.fr       */
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

unsigned int	get_texture_color(t_texture *texture, int tex_x, int tex_y,
		t_data *data)
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

void var_use_in_image(t_var_for_textures *var, float wall_height, int ray_index, t_data *game)
{
    var->wall_top = (WINDOW_HEIGHT - (int)wall_height) / 2;
	if (var->wall_top < 0)
		var->wall_top = 0;
	var->wall_bottom = (WINDOW_HEIGHT + (int)wall_height) / 2;
	if (var->wall_bottom >= WINDOW_HEIGHT)
		var->wall_bottom = WINDOW_HEIGHT - 1;
	var->side = determine_wall_side(game, ray_index);
	if (var->side == NORTH || var->side == SOUTH)
		var->wall_x = game->raycas->ray[ray_index].wall_hit_x;
	else
		var->wall_x = game->raycas->ray[ray_index].wall_hit_y;
	var->wall_x = fmod(var->wall_x, game->size_textures);
	if (var->wall_x < 0)
		var->wall_x += game->size_textures;
	var->tex_x = (int)(var->wall_x * game->texture[var->side].width / game->size_textures);
	if (var->tex_x >= game->texture[var->side].width)
		var->tex_x = game->texture[var->side].width - 1;
	var->step = (double)game->texture[var->side].height / wall_height;
	var->tex_pos = (var->wall_top - WINDOW_HEIGHT / 2.0 + wall_height / 2.0) * var->step;
}

void	draw_textured_wall(t_data *game, int x, float wall_height,
		int ray_index)
{
	t_var_for_textures var;
	unsigned int	color;
	int				y;

    var_use_in_image(&var , wall_height, ray_index, game);
	y = var.wall_top;
	while (y < var.wall_bottom)
	{
		var.tex_y = (int)var.tex_pos & (game->texture[var.side].height - 1);
		color = get_texture_color(&game->texture[var.side], var.tex_x, var.tex_y, game);
		my_mlx_pixel_put(game->img, x, y, color);
		var.tex_pos += var.step;
		y++;
	}
}
