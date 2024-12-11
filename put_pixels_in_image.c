/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixels_in_image.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:00:28 by oel-moue          #+#    #+#             */
/*   Updated: 2024/12/11 21:27:43 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
void draw_linee(t_data *data, double ray_angle)
{
    double	ray_x;
    double	ray_y;
    double	delta_x;
    double	delta_y;
    int		map_x;
    int		map_y;
    int		hit;

    ray_x = data->player->player_x;
    ray_y = data->player->player_y;
    delta_x = cos(ray_angle);
    delta_y = sin(ray_angle);
    hit = 0;
    while (!hit)
    {
        ray_x += delta_x * 0.1;
        ray_y += delta_y * 0.1;
        map_x = (int)ray_x;
        map_y = (int)ray_y;
        if (data->map[map_y][map_x] > 0)
            hit = 1;
        my_mlx_pixel_put(data->img, ray_x * SQUAR_SIZE, ray_y * SQUAR_SIZE, 0xFFFFFF);
    }
}

void	draw_view(t_data *data)
{
    double	start_angle;
    double	ray_angle;
    double	fov;
    int		num_rays;
    int		i;

    fov = 60 * (M_PI / 180); // 60 degrees FOV in radians
    num_rays = data->img->width; // Number of rays to cast
    start_angle = atan2(data->player->player_direction_y, data->player->player_direction_x) - fov / 2;
    i = 0;
    while (i < num_rays)
    {
        ray_angle = start_angle + i * (fov / num_rays);
        draw_linee(data, ray_angle);
        i++;
    }
}
void	draw_player(t_data *data)
{
	int	player_x;
	int	player_y;
	int	player_size;
	int	y;
	int	x;

	player_size = SQUAR_SIZE / 7;
	player_x = data->player->player_x * SQUAR_SIZE;
	player_y = data->player->player_y * SQUAR_SIZE;
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
	draw_view(data);
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
	return (0);
}
