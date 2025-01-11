/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 10:29:48 by oel-moue          #+#    #+#             */
/*   Updated: 2025/01/11 23:57:18 by oel-moue         ###   ########.fr       */
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

unsigned int	get_texture_color(t_texture *texture, int tex_x, int tex_y,
		t_data *data)
{
	char			*pixel;
	unsigned int	color;

	tex_x = tex_x % data->size_textures;
	tex_y = tex_y % data->size_textures;
	pixel = texture->addr + (tex_y * texture->line_length + tex_x
			* (texture->bits_per_pixel / 8));
	color = *(unsigned int *)pixel;
	return (color);
}

void	var_use_in_image(t_var_for_textures *var, float wall_height,
		int ray_index, t_data *game)
{
	var->wall_top = (WINDOW_HEIGHT - (int)wall_height) / 2;
	if (var->wall_top < 0)
		var->wall_top = 0;
	var->wall_bottom = (WINDOW_HEIGHT + (int)wall_height) / 2;
	if (var->wall_bottom >= WINDOW_HEIGHT)
		var->wall_bottom = WINDOW_HEIGHT - 1;
	var->side = determine_wall_side(game, ray_index);
	if (var->side == NORTH || var->side == SOUTH)
		var->wall_x = game->raycas->ray[ray_index].wall_x;
	else
		var->wall_x = game->raycas->ray[ray_index].wall_y;
	var->tex_offset_x = (int)var->wall_x % game->size_textures;
	var->step = (double)game->texture[var->side].height / wall_height;
	var->tex_pos = (var->wall_top - WINDOW_HEIGHT / 2.0 + wall_height / 2.0)
		* var->step;
}

void	draw_textured_wall(t_data *game, int x, float wall_height,
		int ray_index)
{
	t_var_for_textures	var;
	unsigned int		color;
	int					y;

	var_use_in_image(&var, wall_height, ray_index, game);
	y = var.wall_top;
	while (y < var.wall_bottom)
	{
		var.tex_offset_y = (int)var.tex_pos + (game->texture[var.side].height
				- 1);
		color = get_texture_color(&game->texture[var.side], var.tex_offset_x,
				var.tex_offset_y, game);
		my_mlx_pixel_put(game->img, x, y, color);
		var.tex_pos += var.step;
		y++;
	}
}
