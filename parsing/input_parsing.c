/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 18:28:59 by el_cid            #+#    #+#             */
/*   Updated: 2025/01/09 11:09:59 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	initialize_parsing(t_data *game, char *filename)
{
	game->input = malloc(sizeof(t_map));
	if (!game->input)
	{
		printf("Error: Failed to allocate map structure\n");
		exit(1);
	}
	check_file(game, filename);
	game->input->no_texture = NULL;
	game->input->so_texture = NULL;
	game->input->we_texture = NULL;
	game->input->ea_texture = NULL;
	game->input->floor_color[0] = -1;
	game->input->floor_color[1] = -1;
	game->input->floor_color[2] = -1;
	game->input->sky_color[0] = -1;
	game->input->sky_color[1] = -1;
	game->input->sky_color[2] = -1;
	game->input->player_x = -1;
	game->input->player_y = -1;
	game->input->player_dir = 0;
	game->input->map_data = NULL;
	game->input->width = 0;
	game->input->height = 0;
}

int	parse_element(t_data *game, char *line)
{
	if (ft_strnstr(line, "NO ", 3) || ft_strnstr(line, "NO\t", 3))
		parse_texture(game, line, "NO");
	else if (ft_strnstr(line, "SO ", 3) || ft_strnstr(line, "SO\t", 3))
		parse_texture(game, line, "SO");
	else if (ft_strnstr(line, "WE ", 3) || ft_strnstr(line, "WE\t", 3))
		parse_texture(game, line, "WE");
	else if (ft_strnstr(line, "EA ", 3) || ft_strnstr(line, "EA\t", 3))
		parse_texture(game, line, "EA");
	else if (ft_strnstr(line, "F ", 2) || ft_strnstr(line, "F\t", 3))
		parse_color(game, line, 'F');
	else if (ft_strnstr(line, "C ", 2) || ft_strnstr(line, "C\t", 3))
		parse_color(game, line, 'C');
	else
	{
		write(1, "Error\nInvalid element!\n", 24);
		cleanup_up(game, 1);
	}
	return (0);
}

int	process_line(t_data *game, int *elements_done, int *map_begin)
{
	if (!check_parsed_elements(game))
	{
		if (!is_empty_line(game->input->line))
			parse_element(game, game->input->line);
	}
	else
	{
		if (!is_empty_line(game->input->line))
		{
			*elements_done = 1;
			*map_begin = 1;
			handle_map_line(game, game->input->line);
		}
		else if (*map_begin == 1)
			handle_map_line(game, game->input->line);
	}
	return (0);
}

void	validate_map_data(t_data *game)
{
	fill_map_spaces(game);
	validate_map(game);
	if (game->input->player_x == -1)
	{
		write(1, "Error\nPlayer position not found\n", 33);
		cleanup_up(game, 1);
	}
}

int	parse_map(t_data *game, char *filename)
{
	int	elements_done;
	int	map_begin;

	elements_done = 0;
	map_begin = 0;
	initialize_parsing(game, filename);
	game->input->line = get_next_line(game->input->fd);
	while (game->input->line)
	{
		process_line(game, &elements_done, &map_begin);
		free(game->input->line);
		game->input->line = get_next_line(game->input->fd);
	}
	close(game->input->fd);
	if (!elements_done)
	{
		write(1, "Error\nMissing map data\n", 24);
		cleanup_up(game, 1);
	}
	else if (game->input->map_data != NULL)
		validate_map_data(game);
	return (0);
}
