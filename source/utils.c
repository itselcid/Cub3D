/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:11:59 by oel-moue          #+#    #+#             */
/*   Updated: 2025/01/11 15:53:01 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	destroy(t_data *data)
{
	mlx_destroy_image(data->mlx, data->img->img_map);
	free(data->img);
	mlx_destroy_window(data->mlx, data->win);
	free(data->mlx);
}

void	free_raycas(t_data *data)
{
	if (data->raycas)
	{
		if (data->raycas->ray)
			free(data->raycas->ray);
		free(data->raycas);
	}
}

void	cleanup_textures1(t_data *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (data->texture[i].img)
		{
			mlx_destroy_image(data->mlx, data->texture[i].img);
			data->texture[i].img = NULL;
		}
		i++;
	}
}

void	clean_all(t_data *data)
{
	mlx_destroy_image(data->mlx, data->img->img_map);
	mlx_destroy_window(data->mlx, data->win);
	cleanup_textures1(data);
	mlx_destroy_display(data->mlx);
	cleanup_up(data, 0);
	free(data->mlx);
	free(data->img);
	free(data->player);
	free_raycas(data);
	exit(0);
}
