/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 15:45:03 by oel-moue          #+#    #+#             */
/*   Updated: 2024/12/18 23:11:04 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_player(t_data *data)
{
	double	new_x;
	double	new_y;
	double	move_step;

	if (data->player->rotate != 0)
	{
		data->player->angle += data->player->rotate * ROTATE_SPEED;
		normalize_angle(&data->player->angle);
	}
	if (data->player->walk != 0)
	{
		move_step = data->player->walk * MOVE_SPEED;
		new_x = data->player->player_x + cos(data->player->angle) * move_step;
		new_y = data->player->player_y + sin(data->player->angle) * move_step;
	}
	if (data->player->strafe != 0)
	{
		move_step = data->player->strafe * MOVE_SPEED;
		new_x = data->player->player_x + cos(data->player->angle + M_PI / 2)
			* move_step;
		new_y = data->player->player_y + sin(data->player->angle + M_PI / 2)
			* move_step;
	}
	// Check if the new position is valid
	if (new_x >= 0 && new_x < data->img->width && new_y >= 0 && new_y < data->img->height
		&& data->map[(int)new_y][(int)new_x] == '0')
	{
		data->player->player_x = new_x;
		data->player->player_y = new_y;
	}
}
int	key_handler(int key_code, t_data *data)
{
	if (key_code == ESC)
		close_window(data);
	if (key_code == UP) // W
		data->player->walk = 1;
	if (key_code == DOWN) // S
		data->player->walk = -1;
	if (key_code == RIGHT) // D
		data->player->strafe = 1;
	if (key_code == LEFT) // A
		data->player->strafe = -1;
	if (key_code == ROTATE_RIGHT) // -->
		data->player->rotate = 1;
	if (key_code == ROTATE_LEFT) // <--
		data->player->rotate = -1;
	return (0);
}

int	relase_key(int key_code, t_data *data)
{
	if (key_code == UP || key_code == DOWN)
		data->player->walk = 0;
	if (key_code == RIGHT || key_code == LEFT)
		data->player->strafe = 0;
	if (key_code == ROTATE_RIGHT || key_code == ROTATE_LEFT)
		data->player->rotate = 0;
	return (0);
}
