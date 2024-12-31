/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 15:55:26 by oel-moue          #+#    #+#             */
/*   Updated: 2024/12/31 17:25:46 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init_map(t_map *map)
{
	map->fd = 0;
	map->no_texture = NULL;
	map->so_texture = NULL;
	map->we_texture = NULL;
	map->ea_texture = NULL;
	map->floor_color[0] = -1;
	map->floor_color[1] = -1;
	map->floor_color[2] = -1;
	map->sky_color[0] = -1;
	map->sky_color[1] = -1;
	map->sky_color[2] = -1;
	map->player_x = -1;
	map->player_y = -1;
	map->player_dir = 0;
	map->map_data = NULL;
	map->width = 0;
	map->height = 0;
}
void cleanup_up(t_data *game, int num)
{
	if (game->input->line)
		free(game->input->line);
	if (game->input->fd > 0)
		close(game->input->fd);
	if (game->input->no_texture)
		free(game->input->no_texture);
	if (game->input->so_texture)
		free(game->input->so_texture);
	if (game->input->we_texture)
		free(game->input->we_texture);
	if (game->input->ea_texture)
		free(game->input->ea_texture);
	if (game->input->map_data)
	{
		int i = 0;
		while (game->input->map_data[i])
			free(game->input->map_data[i++]);
		free(game->input->map_data);
	}
	if (num == 1)
		exit(1);
}

int check_file_extension(t_data *game, char *filename)
{
	int name_len = ft_strlen(filename);
	if (name_len < 4 || filename[name_len - 4] != '.' || filename[name_len - 3] != 'c' ||
		filename[name_len - 2] != 'u' || filename[name_len - 1] != 'b')
	{
		write(1, "Error\nInvalid file extension.\n", 31);
		cleanup_up(game, 1);
	}
	return (0);
}
int check_texture_extension(t_data *game, char *filename)
{
	int name_len = ft_strlen(filename);
	if (name_len < 4 || filename[name_len - 4] != '.' || filename[name_len - 3] != 'x' ||
		filename[name_len - 2] != 'p' || filename[name_len - 1] != 'm')
	{
		write(1, "Error\nInvalid texture extension.\n", 34);
		cleanup_up(game, 1);
	}
	return (0);
}
int parse_texture(t_data *game, char *line, char *direction)
{
	char **str;
	int fd;
	str = ft_split(line, ' ');
	if (ft_strncmp(str[0], direction, 2) || str[2] != NULL || check_texture_extension(game, str[1]))
	{
		write(1, "Error\nInvalid texture 1.\n", 24);
		cleanup_up(game, 1);
	}

	fd = open(str[1], O_RDONLY);
	if (fd < 0)
	{
		write(1, "Error\nCant acces texture file.\n", 32);
		cleanup_up(game, 1);
	}
	close(fd);
	if (ft_strncmp(direction, "NO", 2) == 0 && game->input->no_texture == NULL)
		game->input->no_texture = ft_strdup(str[1]);
	else if (ft_strncmp(direction, "SO", 2) == 0 && game->input->so_texture == NULL)
		game->input->so_texture = ft_strdup(str[1]);
	else if (ft_strncmp(direction, "WE", 2) == 0 && game->input->we_texture == NULL)
		game->input->we_texture = ft_strdup(str[1]);
	else if (ft_strncmp(direction, "EA", 2) == 0 && game->input->ea_texture == NULL)
		game->input->ea_texture = ft_strdup(str[1]);
	else
	{
		write(1, "Error\nInvalid texture.\n", 24);
		cleanup_up(game, 1);
	}

	return 0;
}

int parse_color(t_data *game, char *line, char direction)
{
	char **str;
	char **colors;
	int commas = 0;
	int i = 0;

	while (line[i])
	{
		if (line[i] == ',')
			commas++;
		i++;
	}
	if (commas != 2)
	{
		write(1, "Error\nInvalid color format.\n", 28);
		cleanup_up(game, 1);
	}

	str = ft_split(line, ' ');
	if (str[2] != NULL || str[0][0] != direction || !str[1])
	{
		write(1, "Error\nInvalid color format.\n", 28);
		cleanup_up(game, 1);
	}

	i = 0;
	while (str[1][i])
	{
		if (!(str[1][i] >= '0' && str[1][i] <= '9') && str[1][i] != ',')
		{
			write(1, "Error\nInvalid color character.\n", 32);
			cleanup_up(game, 1);
		}
		i++;
	}

	colors = ft_split(str[1], ',');
	if (!colors || !colors[0] || !colors[1] || !colors[2])
	{
		write(1, "Error\nInvalid color format.\n", 29);
		cleanup_up(game, 1);
	}
	i = 0;
	while (i < 3)
	{
		if (ft_atoi(colors[i]) < 0 || ft_atoi(colors[i]) > 255)
		{
			write(1, "Error\nColor out of range\n", 26);
			cleanup_up(game, 1);
		}
		if ((direction == 'F' && game->input->floor_color[i] != -1) ||
			(direction == 'C' && game->input->sky_color[i] != -1))
		{
			write(1, "Error\nDuplicated color\n", 24);
			cleanup_up(game, 1);
		}
		i++;
	}

	i = 0;
	while (i < 3)
	{
		if (direction == 'F')
			game->input->floor_color[i] = ft_atoi(colors[i]);
		else if (direction == 'C')
			game->input->sky_color[i] = ft_atoi(colors[i]);
		i++;
	}
	return 0;
}
int is_empty_line(char *line)
{
	int i = 0;

	while (line[i] && (line[i] == ' ' || line[i] == '\t' || line[i] == '\n'))
		i++;
	if (line[i] == '\0')
		return 1;
	return 0;
}
int check_parsed_elements(t_data *game)
{
	if (!game->input->no_texture || !game->input->so_texture ||
		!game->input->we_texture || !game->input->ea_texture ||
		game->input->floor_color[0] == -1 || game->input->sky_color[0] == -1)
		return 0;
	return 1;
}
int handle_map_line(t_data *game, char *line)
{
	char **tmp;
	int i;

	if (game->input->map_data == NULL)
	{
		game->input->map_data = malloc(sizeof(char *) * 2);
		game->input->map_data[0] = ft_strdup(line);
		game->input->map_data[1] = NULL;
		game->input->height = 1;
		game->input->width = ft_strlen(line);
	}
	else
	{
		int old_height = game->input->height;
		tmp = malloc(sizeof(char *) * (old_height + 2));
		i = 0;
		while (i < old_height)
		{
			tmp[i] = game->input->map_data[i];
			i++;
		}
		tmp[i] = ft_strdup(line);
		tmp[i + 1] = NULL;
		free(game->input->map_data);
		game->input->map_data = tmp;
		game->input->height++;
		if (ft_strlen(line) > game->input->width)
			game->input->width = ft_strlen(line);
	}
	return 0;
}
void check_position(t_data *game, int y, int x)
{
	
	if (y == 0 || game->input->map_data[y - 1][x] == ' ' || game->input->map_data[y - 1][x] == '\t')
	{
		write(1, "Error\nMap is not valid\n", 24);
		cleanup_up(game, 1);
	}
	if (game->input->map_data[y + 1][x] == ' ' || game->input->map_data[y + 1][x] == '\t')
	{
		write(1, "Error\nMap is not valid\n", 24);
		cleanup_up(game, 1);
	}

	if (x == 0 || game->input->map_data[y][x - 1] == ' ' || game->input->map_data[y][x - 1] == '\t')
	{
		write(1, "Error\nMap is not valid\n", 24);
		cleanup_up(game, 1);
	}
	if (game->input->map_data[y][x + 1] == ' ')
	{
		write(1, "Error\nMap is not valid\n", 24);
		cleanup_up(game, 1);
	}
	if (game->input->map_data[y][x] == 'N' || game->input->map_data[y][x] == 'S' || game->input->map_data[y][x] == 'E' || game->input->map_data[y][x] == 'W')
	{
		if (game->input->player_x != -1 || game->input->player_y != -1)
		{
			write(1, "Error\nMultiple player positions\n", 33);
			cleanup_up(game, 1);
		}
		game->input->player_x = x;
		game->input->player_y = y;
		game->input->player_dir = game->input->map_data[y][x];
	}
}
void validate_map(t_data *game)
{
	int i = 0;

	while (game->input->map_data[i])
	{
		int j = 0;
		while (game->input->map_data[i][j])
		{
			if (game->input->map_data[i][j] != '1' && game->input->map_data[i][j] != '0' && game->input->map_data[i][j] != 'N' &&
				game->input->map_data[i][j] != 'S' && game->input->map_data[i][j] != 'E' &&
				game->input->map_data[i][j] != 'W' && game->input->map_data[i][j] != ' ' && game->input->map_data[i][j] != '\t')
			{
				write(1, "Error\nInvalid map character\n", 29);
				cleanup_up(game, 1);
			}
			if (game->input->map_data[i][j] == 'N' || game->input->map_data[i][j] == 'S' || game->input->map_data[i][j] == 'E' || game->input->map_data[i][j] == 'W' || game->input->map_data[i][j] == '0')
			{
				check_position(game, i, j);
			}
			j++;
		}

		i++;
	}
}
void fill_map_spaces(t_data *game)
{
	int i = 0;
	while (i < game->input->height)
	{
		int line_len = ft_strlen(game->input->map_data[i]);
		if (line_len < game->input->width)
		{
			char *new_line = malloc(game->input->width + 1);
			ft_memset(new_line, ' ', game->input->width);
			new_line[game->input->width] = '\0';
			ft_memcpy(new_line, game->input->map_data[i], line_len);
			free(game->input->map_data[i]);
			game->input->map_data[i] = new_line;
		}
		i++;
	}
}

int parse_map(t_data *game, char *filename)
{
	int elements_done = 0;
	int map_begin = 0;

	game->input = malloc(sizeof(t_map));
	if (!game->input)
	{
		printf("Error: Failed to allocate map structure\n");
		exit(1);
	}
	init_map(game->input);
	game->input->fd = open(filename, O_RDONLY);
	if (game->input->fd < 0 || check_file_extension(game, filename))
		return 1;

	game->input->line = get_next_line(game->input->fd);
	while (game->input->line)
	{
		if (!check_parsed_elements(game))
		{
			if (!is_empty_line(game->input->line))
			{
				if (ft_strnstr(game->input->line, "NO ", 3) || ft_strnstr(game->input->line, "NO\t", 3))
					parse_texture(game, game->input->line, "NO");
				else if (ft_strnstr(game->input->line, "SO ", 3) || ft_strnstr(game->input->line, "SO\t", 3))
					parse_texture(game, game->input->line, "SO");
				else if (ft_strnstr(game->input->line, "WE ", 3) || ft_strnstr(game->input->line, "WE\t", 3))
					parse_texture(game, game->input->line, "WE");
				else if (ft_strnstr(game->input->line, "EA ", 3) || ft_strnstr(game->input->line, "EA\t", 3))
					parse_texture(game, game->input->line, "EA");
				else if (ft_strnstr(game->input->line, "F ", 2) || ft_strnstr(game->input->line, "F\t", 3))
					parse_color(game, game->input->line, 'F');
				else if (ft_strnstr(game->input->line, "C ", 2) || ft_strnstr(game->input->line, "C\t", 3))
					parse_color(game, game->input->line, 'C');
				else
				{
					write(1, "Error\nInvalid element!\n", 24);
					cleanup_up(game, 1);
				}
			}
		}
		else
		{
			if (!is_empty_line(game->input->line))
			{
				elements_done = 1;
				map_begin = 1;
				handle_map_line(game, game->input->line);
			}
			else if (map_begin)
				handle_map_line(game, game->input->line);
		}
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
	{
		int i = 0;

		fill_map_spaces(game);

		while (game->input->map_data[i])
		{
			printf("%s\n", game->input->map_data[i]);
			i++;
		}

		validate_map(game);
	}
	return 0;
}
