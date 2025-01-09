/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 16:55:53 by el_cid            #+#    #+#             */
/*   Updated: 2025/01/07 14:01:55 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	is_valid_char(char c)
{
	return (c == '1' || c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| c == ' ' || c == '\t');
}

void	initialize_map_data(t_data *game, char *line)
{
	game->input->map_data = malloc(sizeof(char *) * 2);
	if (!game->input->map_data)
	{
		write(1, "Error\nMemory allocation failed\n", 31);
		cleanup_up(game, 1);
	}
	game->input->map_data[0] = ft_strdup(line);
	game->input->map_data[1] = NULL;
	game->input->height = 1;
	game->input->width = ft_strlen(line);
}

int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t' || line[i] == '\n'))
		i++;
	if (line[i] == '\0')
		return (1);
	return (0);
}

int	check_parsed_elements(t_data *game)
{
	if (!game->input->no_texture || !game->input->so_texture
		|| !game->input->we_texture || !game->input->ea_texture
		|| game->input->floor_color[0] == -1 || game->input->sky_color[0] == -1)
		return (0);
	return (1);
}

void	fill_map_spaces(t_data *game)
{
	int		i;
	int		line_len;
	char	*new_line;

	i = 0;
	while (i < game->input->height)
	{
		line_len = ft_strlen(game->input->map_data[i]);
		if (line_len < game->input->width)
		{
			new_line = malloc(game->input->width + 1);
			if (!new_line)
			{
				write(1, "Error\nMemory allocation failed\n", 31);
				cleanup_up(game, 1);
			}
			ft_memset(new_line, ' ', game->input->width);
			new_line[game->input->width] = '\0';
			ft_memcpy(new_line, game->input->map_data[i], line_len);
			free(game->input->map_data[i]);
			game->input->map_data[i] = new_line;
		}
		i++;
	}
}
