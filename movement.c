/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 15:45:03 by oel-moue          #+#    #+#             */
/*   Updated: 2025/01/03 22:06:35 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void check_collision(t_data *data, float new_x, float new_y)
{
    // Get the map grid coordinates
    int map_grid_x = (int)(new_x / SQUAR_SIZE);
    int map_grid_y = (int)(new_y / SQUAR_SIZE);
    
    // Check if the new position would be inside a wall
    if (data->input->map_data[map_grid_y][map_grid_x] == '1')
        return; // Don't update position if we'd hit a wall
    
    // If no collision, update position
    data->player->player_x = new_x;
    data->player->player_y = new_y;
} 

void validate_move(t_data *data, double new_x, double new_y)
{
	if (new_x >= 0 && new_x < data->img->width && new_y >= 0 && new_y < data->img->height
		&& data->input->map_data[(int)(new_y)][(int)(new_x)] != '1')
	{
		data->player->player_x = new_x;
		data->player->player_y = new_y;
	}
}
void	move_player(t_data *data)
{
	double	new_x = 0;
	double	new_y = 0;
	double	move_step;
	if (data->player->rotate != 0)
	{
		data->player->angle += data->player->rotate * ROTATE_SPEED;
		normalize_angle(&data->player->angle);
	}
	if (data->player->Movement_walk != 0)
	{
		move_step = data->player->Movement_walk * MOVE_SPEED;
		new_x = data->player->player_x + cos(data->player->angle) * move_step;
		new_y = data->player->player_y + sin(data->player->angle) * move_step;
	}
	if (data->player->Movement_sideways != 0)
	{
		move_step = data->player->Movement_sideways * MOVE_SPEED;
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
	if (key_code == UP) // W
		data->player->Movement_walk = 1;
	if (key_code == DOWN) // S
		data->player->Movement_walk = -1;
	if (key_code == RIGHT) // D
		data->player->Movement_sideways = 1;
	if (key_code == LEFT) // A
		data->player->Movement_sideways = -1;
	if (key_code == ROTATE_RIGHT) // -->
		data->player->rotate = 1;
	if (key_code == ROTATE_LEFT) // <--
		data->player->rotate = -1;
	return (0);
}

int	relase_key(int key_code, t_data *data)
{
	if (key_code == UP || key_code == DOWN)
		data->player->Movement_walk = 0;
	if (key_code == RIGHT || key_code == LEFT)
		data->player->Movement_sideways = 0;
	if (key_code == ROTATE_RIGHT || key_code == ROTATE_LEFT)
		data->player->rotate = 0;
	return (0);
}
