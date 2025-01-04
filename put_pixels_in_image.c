/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixels_in_image.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:00:28 by oel-moue          #+#    #+#             */
/*   Updated: 2025/01/04 12:48:11 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_image *img, int x, int y, unsigned int color)
{
	char	*dst;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void ft_draw_line(t_data *data, int start_x, int start_y, int end_x, int end_y)
{
	double delta_x = end_x - start_x;
	double delta_y = end_y - start_y;
	double steps = fmax(fabs(delta_x), fabs(delta_y));

	double x_increment = delta_x / steps;
	double y_increment = delta_y / steps;

	double x = start_x;
	double y = start_y;
	int i = 0;
	while (i <= steps)
	{
		my_mlx_pixel_put(data->img,(int)x, (int)y, 0x00FF00);
		x += x_increment;
		y += y_increment;
		i++;
	}
}

void	normalize_angle(float *angle)
{
	while (*angle >= 2 * M_PI)
		*angle -= 2 * M_PI;
	while (*angle < 0)
		*angle += 2 * M_PI;
}

void	draw_player(t_data *data)
{
	int	player_x;
	int	player_y;
	int	player_size;
	int	y;
	int	x;

	player_size = data->size_textures / 7;
	player_x = data->player->player_x * data->size_textures;
	player_y = data->player->player_y * data->size_textures;
	int player_color = 0xFF0000; // Red color for player
	y = 0;
	while (y < player_size)
	{
		x = 0;
		while (x < player_size)
		{
			my_mlx_pixel_put(data->img, player_x + x, player_y + y,
				player_color);
			x++;
		}
		y++;
	}
}

int	put_color_with_pixels(t_data *data)
{
	int	line;
	int	colone;
	int	tile_x;
	int	tile_y;
	int	color;
	int	y;
	int	x;

	line = 0;
	while (line < data->h)
	{
		colone = 0;
		while (colone < data->w)
		{
			tile_x = colone * data->size_textures;
			tile_y = line * data->size_textures;
			if (data->input->map_data[line][colone] == '1')
			{
				color = 0x444444;
			}
			else
				color = 0xFFFFFF;
			y = tile_y;
			while (y < tile_y + data->size_textures)
			{
				x = tile_x;
				while (x < tile_x + data->size_textures)
				{
					if (y == tile_y || y == tile_y + data->size_textures - 1
						|| x == tile_x || x == tile_x + data->size_textures - 1)
						my_mlx_pixel_put(data->img, x, y, 0x000000);
					else
						my_mlx_pixel_put(data->img, x, y, color);
					x++;
				}
				y++;
			}
			colone++;
		}
		line++;
	}
	return (0);
}
