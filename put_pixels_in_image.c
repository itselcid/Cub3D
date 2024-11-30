/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixels_in_image.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:00:28 by oel-moue          #+#    #+#             */
/*   Updated: 2024/11/28 16:01:55 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_player(t_data *data)
{
	int	i;
	int	j;
	int	player_x;
	int	player_y;
	int	player_size;
	int	y;
	int	x;

	i = 0;
	while (i < data->h)
	{
		j = 0;
		while (j < ft_strlen_not_newline(data->map[i]))
		{
			if (data->map[i][j] == 'N')
			{
				data->player->palyer_dir_y = i;
				data->player->palyer_dir_x = j;
				break ;
			}
			j++;
		}
		i++;
	}
	player_size = SQUAR_SIZE / 3;
	player_x = data->player->palyer_dir_x * SQUAR_SIZE;
	player_y = data->player->palyer_dir_y * SQUAR_SIZE;
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
		while (colone < ft_strlen_not_newline(data->map[line]))
		{
			tile_x = colone * SQUAR_SIZE;
			tile_y = line * SQUAR_SIZE;
			if (data->map[line][colone] == '1')
				color = 0x444444;
			else
				color = 0xFFFFFF;
			y = tile_y;
			while (y < tile_y + SQUAR_SIZE)
			{
				x = tile_x;
				while (x < tile_x + SQUAR_SIZE)
				{
					if (y == tile_y || y == tile_y + SQUAR_SIZE - 1
						|| x == tile_x || x == tile_x + SQUAR_SIZE - 1)
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
	draw_player(data);
	if (data->win && data->img->img_map)
		mlx_put_image_to_window(data->mlx, data->win, data->img->img_map, 0, 0);
	return (0);
}
