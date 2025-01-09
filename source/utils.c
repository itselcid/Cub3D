/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 11:11:59 by oel-moue          #+#    #+#             */
/*   Updated: 2025/01/09 11:13:29 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	destroy(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_image(data->mlx, data->img->img_map);
	free(data->img);
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
