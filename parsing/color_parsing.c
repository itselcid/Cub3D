/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: el_cid <el_cid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 23:33:34 by el_cid            #+#    #+#             */
/*   Updated: 2025/01/08 23:26:45 by el_cid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	validate_color_format(char *line, int *commas, t_data *game)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == ',')
			(*commas)++;
		i++;
	}
	if (*commas != 2)
	{
		write(1, "Error\nInvalid color format: Expected 2 commas", 46);
		cleanup_up(game, 1);
	}
}

void	validate_color_characters(char *color_str, t_data *game, char **str)
{
	int	i;

	i = 0;
	while (color_str[i])
	{
		if (!(color_str[i] >= '0' && color_str[i] <= '9')
			&& color_str[i] != ',')
		{
			printf("Error\nInvalid color character: '");
			printf("%c' is not a digit or comma.\n", color_str[i]);
			free_split(str);
			cleanup_up(game, 1);
		}
		i++;
	}
}

void	validate_and_put_colors(t_data *game, char **colors, char direction,
		char **str)
{
	int	i;

	i = -1;
	while (++i < 3)
	{
		if (ft_atoi(colors[i]) < 0 || ft_atoi(colors[i]) > 255)
		{
			printf("Error\nColor value out of range.\n");
			free_split(colors);
			free_split(str);
			cleanup_up(game, 1);
		}
		if ((direction == 'F' && game->input->floor_color[i] != -1)
			|| (direction == 'C' && game->input->sky_color[i] != -1))
		{
			printf("Error\nDuplicated color\n");
			free_split(colors);
			free_split(str);
			cleanup_up(game, 1);
		}
		if (direction == 'F')
			game->input->floor_color[i] = ft_atoi(colors[i]);
		else if (direction == 'C')
			game->input->sky_color[i] = ft_atoi(colors[i]);
	}
}

void	process_color_string(t_data *game, char *color_str, char direction,
		char **str)
{
	char	**colors;

	colors = ft_split(color_str, ',');
	if (!colors || !colors[0] || !colors[1] || !colors[2])
	{
		write(1, "Error\nInvalid color format: ", 27);
		write(1, "Expected 3 values separated by commas.\n", 38);
		free_split(str);
		cleanup_up(game, 1);
	}
	validate_and_put_colors(game, colors, direction, str);
	free_split(colors);
}

int	parse_color(t_data *game, char *line, char direction)
{
	char	**str;
	int		commas;

	commas = 0;
	validate_color_format(line, &commas, game);
	str = ft_split(line, ' ');
	if (!str || str[2] != NULL || !str[0] || str[0][0] != direction || !str[1])
	{
		write(1, "Error\nInvalid color format: Expected '", 38);
		write(1, &direction, 1);
		write(1, " <R,G,B>' format.\n", 18);
		if (str)
			free_split(str);
		cleanup_up(game, 1);
	}
	validate_color_characters(str[1], game, str);
	process_color_string(game, str[1], direction, str);
	free_split(str);
	return (0);
}
