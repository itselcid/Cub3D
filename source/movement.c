/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: el_cid <el_cid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 15:45:03 by oel-moue          #+#    #+#             */
/*   Updated: 2025/01/07 19:23:13 by el_cid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	validate_move(t_data *data, double new_x, double new_y)
{
	if (new_x >= 0 && new_x < data->img->width && new_y >= 0
		&& new_y < data->img->height
		&& data->input->map_data[(int)(new_y)][(int)(new_x)] != '1')
	{
		data->player->player_x = new_x;
		data->player->player_y = new_y;
	}
}

void	move_player(t_data *data)
{
	double	new_x;
	double	new_y;
	double	move_step;

	new_x = 0;
	new_y = 0;
	if (data->player->rotate != 0)
		data->player->angle += data->player->rotate * ROTATE_SPEED;
	if (data->player->movement_walk != 0)
	{
		move_step = data->player->movement_walk * MOVE_SPEED;
		new_x = data->player->player_x + cos(data->player->angle) * move_step;
		new_y = data->player->player_y + sin(data->player->angle) * move_step;
	}
	if (data->player->movement_sideways != 0)
	{
		move_step = data->player->movement_sideways * MOVE_SPEED;
		new_x = data->player->player_x + cos(data->player->angle + M_PI / 2)
			* move_step;
		new_y = data->player->player_y + sin(data->player->angle + M_PI / 2)
			* move_step;
	}
	validate_move(data, new_x, new_y);
}

int	key_handler(int key_code, t_data *data)
{
	if (key_code == ESC)
		close_window(data);
	if (key_code == UP)
		data->player->movement_walk = 1;
	if (key_code == DOWN)
		data->player->movement_walk = -1;
	if (key_code == RIGHT)
		data->player->movement_sideways = 1;
	if (key_code == LEFT)
		data->player->movement_sideways = -1;
	if (key_code == ROTATE_RIGHT)
		data->player->rotate = 1;
	if (key_code == ROTATE_LEFT)
		data->player->rotate = -1;
	return (0);
}

int	relase_key(int key_code, t_data *data)
{
	if (key_code == UP || key_code == DOWN)
		data->player->movement_walk = 0;
	if (key_code == RIGHT || key_code == LEFT)
		data->player->movement_sideways = 0;
	if (key_code == ROTATE_RIGHT || key_code == ROTATE_LEFT)
		data->player->rotate = 0;
	return (0);
}
