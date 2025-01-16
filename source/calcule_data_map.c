/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcule_data_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: el_cid <el_cid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 10:53:58 by oel-moue          #+#    #+#             */
/*   Updated: 2025/01/16 23:02:30 by el_cid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	calcule_width(char *line)
{
	int	i;

	i = 0;
	while (line[i])
		i++;
	return (i);
}

void	check_direction(t_data *data, float x, float y)
{
	char	c;

	c = data->input->map_data[(int)y][(int)x];
	if (c == 'N')
		data->player->angle = 3 * M_PI / 2;
	else if (c == 'S')
		data->player->angle = M_PI / 2;
	else if (c == 'E')
		data->player->angle = 0;
	else if (c == 'W')
		data->player->angle = M_PI;
}

void	init_raycas(t_data *data)
{
	data->raycas = malloc(sizeof(t_raycas));
	if (data->raycas == NULL)
		exit(1);
	data->raycas->nbr_ray = data->img->width;
	data->raycas->ray = malloc(data->raycas->nbr_ray * sizeof(t_rays));
	if (data->raycas->ray == NULL)
	{
		exit(1);
	}
}

int	close_window(t_data *data)
{
	clean_all(data);
	return (0);
}

void	init_image_and_ray(t_data *data)
{
	data->player->player_x = 0;
	data->player->player_x = data->input->player_x + 0.5;
	data->player->player_y = 0;
	data->player->player_y = data->input->player_y + 0.5;
	check_direction(data, data->player->player_x, data->player->player_y);
	init_image(data);
	data->h = data->input->height;
	data->w = data->input->width;
	data->win = mlx_new_window(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D");
	if (!data->win)
	{
		printf("Error: Failed to create window\n");
		exit(0);
	}
	data->img->height = WINDOW_HEIGHT;
	data->img->width = WINDOW_WIDTH;
	init_raycas(data);
}
