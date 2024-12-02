/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 18:07:54 by oel-moue          #+#    #+#             */
/*   Updated: 2024/12/02 19:06:11 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_up(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player->player_x + data->player->player_direction_x
		* MOVE_SPEED;
	new_y = data->player->player_y + data->player->player_direction_y
		* MOVE_SPEED;
	if (new_x >= 0 && new_x < data->img->width / SQUAR_SIZE && new_y >= 0
		&& new_y < data->h && data->map[(int)new_y][(int)new_x] == '0')
	{
		data->player->player_x = new_x;
		data->player->player_y = new_y;
	}
} 

void	move_down(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player->player_x - data->player->player_direction_x
		* MOVE_SPEED;
	new_y = data->player->player_y - data->player->player_direction_y
		* MOVE_SPEED;
	if (new_x >= 0 && new_x < data->img->width / SQUAR_SIZE && new_y >= 0
		&& new_y < data->h && data->map[(int)new_y][(int)new_x] == '0')
	{
		data->player->player_x = new_x;
		data->player->player_y = new_y;
	}
}

void	move_left(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player->player_x - data->player->plane_x * MOVE_SPEED;
	new_y = data->player->player_y - data->player->plane_y * MOVE_SPEED;
	if (new_x >= 0 && new_x < data->img->width / SQUAR_SIZE && new_y >= 0
		&& new_y < data->h && data->map[(int)new_y][(int)new_x] == '0')
	{
		data->player->player_x = new_x;
		data->player->player_y = new_y;
	}
}

void	move_right(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player->player_x + data->player->plane_x * MOVE_SPEED;
	new_y = data->player->player_y + data->player->plane_y * MOVE_SPEED;
	if (new_x >= 0 && new_x < data->img->width / SQUAR_SIZE && new_y >= 0
		&& new_y < data->h && data->map[(int)new_y][(int)new_x] == '0')
	{
		data->player->player_x = new_x;
		data->player->player_y = new_y;
	}
}