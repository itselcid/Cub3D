/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 16:38:07 by oel-moue          #+#    #+#             */
/*   Updated: 2024/11/24 22:42:04 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_data(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
	{
		printf("Error\n");
		exit(0);
	}
    data->img = malloc(sizeof(t_image));
    if (!data->img)
	{
		printf("Error\n");
		exit(0);
	}
    data->img->height = 0;
    data->img->width = 0;
    data->img->img0 = NULL;
    data->img->img1 = NULL;
    data->h = 0;
	data->up = 0;
	data->down = 0;
	data->left = 0;
	data->right = 0;
}
