/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 16:54:03 by el_cid            #+#    #+#             */
/*   Updated: 2025/01/07 14:01:55 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	validate_and_open_texture(t_data *game, char **str, char *direction)
{
	int	fd;

	if (ft_strncmp(str[0], direction, 2) || str[2] != NULL
		|| check_texture_extension(game, str[1]))
	{
		write(1, "Error\nInvalid texture format.\n", 30);
		cleanup_up(game, 1);
	}
	fd = open(str[1], O_RDONLY);
	if (fd < 0)
	{
		write(1, "Error\nCant access texture file.\n", 33);
		cleanup_up(game, 1);
	}
	close(fd);
	return (0);
}

int	put_texture(t_data *game, char **str, char *direction)
{
	if (ft_strncmp(direction, "NO", 2) == 0 && game->input->no_texture == NULL)
		game->input->no_texture = ft_strdup(str[1]);
	else if (ft_strncmp(direction, "SO", 2) == 0
		&& game->input->so_texture == NULL)
		game->input->so_texture = ft_strdup(str[1]);
	else if (ft_strncmp(direction, "WE", 2) == 0
		&& game->input->we_texture == NULL)
		game->input->we_texture = ft_strdup(str[1]);
	else if (ft_strncmp(direction, "EA", 2) == 0
		&& game->input->ea_texture == NULL)
		game->input->ea_texture = ft_strdup(str[1]);
	else
	{
		write(1, "Error\nInvalid texture.\n", 24);
		cleanup_up(game, 1);
	}
	return (0);
}

int	parse_texture(t_data *game, char *line, char *direction)
{
	char	**str;

	str = ft_split(line, ' ');
	if (!str)
	{
		write(1, "Error\nMemory allocation failed.\n", 32);
		cleanup_up(game, 1);
	}
	validate_and_open_texture(game, str, direction);
	put_texture(game, str, direction);
	free_split(str);
	return (0);
}
