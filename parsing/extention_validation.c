/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extention_validation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: el_cid <el_cid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 16:57:01 by el_cid            #+#    #+#             */
/*   Updated: 2025/01/07 18:33:47 by el_cid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	check_file(t_data *game, char *filename)
{
	int	name_len;

	game->input->fd = open(filename, O_RDONLY);
	if (game->input->fd < 0)
	{
		write(1, "Error\nInvalid file\n", 20);
		cleanup_up(game, 1);
	}
	name_len = ft_strlen(filename);
	if (name_len < 4 || filename[name_len - 4] != '.'
		|| filename[name_len - 3] != 'c' || filename[name_len - 2] != 'u'
		|| filename[name_len - 1] != 'b')
	{
		write(1, "Error\nInvalid file extension.\n", 31);
		cleanup_up(game, 1);
	}
}

int	check_texture_extension(t_data *game, char *filename)
{
	int	name_len;

	name_len = ft_strlen(filename);
	if (name_len < 4 || filename[name_len - 4] != '.'
		|| filename[name_len - 3] != 'x'
		|| filename[name_len - 2] != 'p'
		|| filename[name_len - 1] != 'm')
	{
		write(1, "Error\nInvalid texture extension.\n", 34);
		cleanup_up(game, 1);
	}
	return (0);
}
