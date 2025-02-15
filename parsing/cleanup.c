/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 18:10:46 by el_cid            #+#    #+#             */
/*   Updated: 2025/01/10 20:57:00 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	cleanup_textures(t_data *game)
{
	if (game->input->no_texture)
		free(game->input->no_texture);
	if (game->input->so_texture)
		free(game->input->so_texture);
	if (game->input->we_texture)
		free(game->input->we_texture);
	if (game->input->ea_texture)
		free(game->input->ea_texture);
}

void	cleanup_map_data(t_data *game)
{
	int	i;

	if (game->input->map_data)
	{
		i = 0;
		while (game->input->map_data[i])
			free(game->input->map_data[i++]);
		free(game->input->map_data);
	}
}

void	cleanup_up(t_data *game, int num)
{
	if (game->input->fd > 0)
		close(game->input->fd);
	if (game->input->line)
		free(game->input->line);
	cleanup_textures(game);
	cleanup_map_data(game);
	if (game->input)
		free(game->input);
	get_next_line(-2);
	if (num == 1)
		exit(1);
}

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

char	**freemem(int i, char **result)
{
	while (i >= 0)
	{
		free(result[i]);
		i--;
	}
	free(result);
	return (NULL);
}
