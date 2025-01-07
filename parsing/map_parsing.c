/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 22:39:58 by el_cid            #+#    #+#             */
/*   Updated: 2025/01/07 16:07:44 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	append_map_line(t_data *game, char *line)
{
	char	**tmp;
	int		i;
	int		old_height;

	old_height = game->input->height;
	tmp = malloc(sizeof(char *) * (old_height + 2));
	if (!tmp)
	{
		write(1, "Error\nMemory allocation failed\n", 31);
		cleanup_up(game, 1);
	}
	i = -1;
	while (++i < old_height)
		tmp[i] = game->input->map_data[i];
	tmp[i] = ft_strdup(line);
	tmp[i + 1] = NULL;
	free(game->input->map_data);
	game->input->map_data = tmp;
	game->input->height++;
	if (ft_strlen(line) > game->input->width)
		game->input->width = ft_strlen(line);
}

int	handle_map_line(t_data *game, char *line)
{
	if (game->input->map_data == NULL)
		initialize_map_data(game, line);
	else
		append_map_line(game, line);
	return (0);
}

void	validate_position(t_data *game, int y, int x)
{
	if (y == 0 || game->input->map_data[y - 1][x] == ' '
		|| game->input->map_data[y - 1][x] == '\0')
	{
		write(1, "Error\nMap is not valid\n", 24);
		cleanup_up(game, 1);
	}
	if (game->input->map_data[y + 1] == NULL
		|| game->input->map_data[y + 1][x] == ' ')
	{
		write(1, "Error\nMap is not valid\n", 24);
		cleanup_up(game, 1);
	}
	if (x == 0 || game->input->map_data[y][x - 1] == ' '
		|| game->input->map_data[y][x - 1] == '\0')
	{
		write(1, "Error\nMap is not valid\n", 24);
		cleanup_up(game, 1);
	}
	if (game->input->map_data[y][x + 1] == ' ' || game->input->map_data[y][x
		+ 1] == '\0')
	{
		write(1, "Error\nMap is not valid\n", 24);
		cleanup_up(game, 1);
	}
}

void	check_position(t_data *game, int y, int x)
{
	validate_position(game, y, x);
	if (game->input->map_data[y][x] == 'N' || game->input->map_data[y][x] == 'S'
		|| game->input->map_data[y][x] == 'E'
		|| game->input->map_data[y][x] == 'W')
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

void	validate_map(t_data *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->input->map_data[i])
	{
		j = 0;
		while (game->input->map_data[i][j])
		{
			if (!is_valid_char(game->input->map_data[i][j]))
			{
				write(1, "Error\nInvalid map character\n", 29);
				cleanup_up(game, 1);
			}
			if (game->input->map_data[i][j] == 'N'
				|| game->input->map_data[i][j] == 'S'
				|| game->input->map_data[i][j] == 'E'
				|| game->input->map_data[i][j] == 'W'
				|| game->input->map_data[i][j] == '0')
				check_position(game, i, j);
			j++;
		}
		i++;
	}
}
