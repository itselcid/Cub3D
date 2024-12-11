/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 16:38:07 by oel-moue          #+#    #+#             */
/*   Updated: 2024/12/11 18:58:47 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_data(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
	{
		printf("Error: MLX initialization failed\n");
		exit(1);
	}
	data->img = malloc(sizeof(t_image));
	if (!data->img)
	{
		printf("Error: Failed to allocate image structure\n");
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		exit(1);
	}
	ft_memset(data->img, 0, sizeof(t_image));
	data->player = malloc(sizeof(t_player));
	data->raycas = malloc(sizeof(t_raycas));
	if (!data->player)
	{
		printf("Error: Failed to allocate player structure\n");
		free(data->img);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		exit(1);
	}
	ft_memset(data->player, 0, sizeof(t_player));
	ft_memset(data->raycas, 0, sizeof(t_raycas));
	data->player->player_x = 0;
	data->player->player_y = 0;
	data->player->player_direction_x = 1.0;//direction vector 
	data->player->player_direction_y = 0.0;

	data->player->plane_x = 0.0; // the camera is Perpendicular to direction
	data->player->plane_y = 0.66;
	data->map = NULL;
	data->h = 0;
	data->up = 0;
	data->down = 0;
	data->left = 0;
	data->right = 0;
	data->raycas->angle_view = 0.66;
	data->raycas->fisrt_intersection_by_x = 0;
	data->raycas->y_step = 0;
	data->raycas->x_step = 0;
}

void	init_image(t_data *data)
{
	if (!data->map)
		return ;
	data->img->img_map = mlx_new_image(data->mlx, data->img->width,
			data->img->height);
	if (!data->img->img_map)
	{
		printf("Error creating image\n");
		exit(0);
	}
	data->img->addr = mlx_get_data_addr(data->img->img_map,
			&data->img->bits_per_pixel, &data->img->line_length,
			&data->img->endian);
}
