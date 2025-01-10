/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 16:38:07 by oel-moue          #+#    #+#             */
/*   Updated: 2025/01/10 22:47:55 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	for_free(t_data *data)
{
	printf("Error: Failed to allocate player structure1\n");
	free(data->img);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(1);
}

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
		for_free(data);
	}
	ft_memset(data->player, 0, sizeof(t_player));
	data->player->angle = 0.0;
}

t_texture	init_for_image(t_data *data, char *path, t_e_texture side)
{
	t_texture	texture;

	texture.img = mlx_xpm_file_to_image(data->mlx, path, &texture.width,
			&texture.height);
	if (!texture.img)
	{
		printf("Error: Failed texture %s\n", path);
		cleanup_up(data, 1);
		destroy(data);
	}
	if (texture.width != 64 || texture.height != 64)
	{
		printf("Error : size is not 64\n");
		cleanup_up(data, 1);
		destroy(data);
	}
	texture.addr = mlx_get_data_addr(texture.img, &texture.bits_per_pixel,
			&texture.line_length, &texture.endian);
	texture.texture_side = side;
	return (texture);
}

void	init_texture(t_data *data)
{
	data->texture[NORTH] = init_for_image(data, data->input->no_texture, NORTH);
	data->texture[SOUTH] = init_for_image(data, data->input->so_texture, SOUTH);
	data->texture[WEST] = init_for_image(data, data->input->we_texture, WEST);
	data->texture[EAST] = init_for_image(data, data->input->ea_texture, EAST);
	data->size_textures = data->texture[NORTH].width;
}

void	init_image(t_data *data)
{
	if (!data->input)
		return ;
	data->img->img_map = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!data->img->img_map)
	{
		printf("Error creating image\n");
		exit(0);
	}
	data->img->addr = mlx_get_data_addr(data->img->img_map,
			&data->img->bits_per_pixel, &data->img->line_length,
			&data->img->endian);
	data->img->width = WINDOW_WIDTH;
	data->img->height = WINDOW_HEIGHT;
	init_texture(data);
}
