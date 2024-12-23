/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 16:38:07 by oel-moue          #+#    #+#             */
/*   Updated: 2024/12/23 11:06:34 by oel-moue         ###   ########.fr       */
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
	if (!data->player)
	{
		printf("Error: Failed to allocate player structure\n");
		free(data->img);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		exit(1);
	}
	ft_memset(data->player, 0, sizeof(t_player));
	data->player->player_y = 0;
	data->map = NULL;
	data->player->angle = 0.0;
}

t_texture	init_for_image(t_data *data, char *path, t_e_texture side)
{
    t_texture	texture;

    texture.img = mlx_xpm_file_to_image(data->mlx, path, &texture.width, &texture.height);
    if (!texture.img)
    {
        printf("Error: Failed texture %s\n", path);
        exit(0);
    }
    texture.addr = mlx_get_data_addr(texture.img, &texture.bits_per_pixel,
                                    &texture.line_length, &texture.endian);
    texture.texture_side = side;
    return (texture);
}

void init_texture(t_data *data)
{
	data->texture[NORTH] = init_for_image(data, "texture/W.xpm", NORTH);
	data->texture[SOUTH] = init_for_image(data, "texture/W.xpm", SOUTH);
	data->texture[WEST] = init_for_image(data, "texture/N1.xpm", WEST);
	data->texture[EAST] = init_for_image(data, "texture/N1.xpm", EAST);
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
	init_texture(data);
}
