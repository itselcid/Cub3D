/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:17:30 by oel-moue          #+#    #+#             */
/*   Updated: 2024/12/12 16:23:58 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_direction_and_camera_left(t_data *data)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->player->player_direction_x;
	old_plane_x = data->player->plane_x;
	double rot_speed = -ANGLE_TO_ROTATE;
	data->player->player_direction_x = old_dir_x * cos(rot_speed)
		- data->player->player_direction_y * sin(rot_speed);
	data->player->player_direction_y = old_dir_x * sin(rot_speed)
		+ data->player->player_direction_y * cos(rot_speed);
	printf("player_direction_x : %f\n", data->player->player_direction_x);
	printf("player_direction_y : %f\n", data->player->player_direction_y);
    // for the camera (plan perpenducular to direction)
	data->player->plane_x = old_plane_x * cos(rot_speed) - data->player->plane_y
		* sin(rot_speed);
	data->player->plane_y = old_plane_x * sin(rot_speed) + data->player->plane_y
		* cos(rot_speed);
}

void	rotate_direction_and_camera_right(t_data *data)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->player->player_direction_x;
	old_plane_x = data->player->plane_x;
	double rot_speed = ANGLE_TO_ROTATE;
	// printf("rot_speed in degree : %f\n", 180 *rot_speed / M_PI);
	data->player->player_direction_x = old_dir_x * cos(rot_speed)
		- data->player->player_direction_y * sin(rot_speed);
	data->player->player_direction_y = old_dir_x * sin(rot_speed)
		+ data->player->player_direction_y * cos(rot_speed);
	printf("player_direction_x : %f\n", data->player->player_direction_x);
	printf("player_direction_y : %f\n", data->player->player_direction_y);
	//plan 
	data->player->plane_x = old_plane_x * cos(rot_speed) - data->player->plane_y
		* sin(rot_speed);
	data->player->plane_y = old_plane_x * sin(rot_speed) + data->player->plane_y
		* cos(rot_speed);
}
