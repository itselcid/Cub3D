/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: el_cid <el_cid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 15:12:38 by oessaadi          #+#    #+#             */
/*   Updated: 2025/01/09 16:54:48 by el_cid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char	*ft_line(char *str)
{
	char	*line;
	int		i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	line = malloc(i + 1);
	ft_strncpy(line, str, i);
	line[i] = '\0';
	return (line);
}

char	*ft_rest(char *str)
{
	char	*rest;
	int		i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\0')
		return (NULL);
	rest = malloc(ft_strlen(str) - i + 1);
	ft_strncpy(rest, &str[i + 1], ft_strlen(str) - i + 1);
	return (rest);
}

char	*read_from_file(int fd, char *rest, char *buff, ssize_t *chars_readed)
{
	char	*tmp;

	*chars_readed = read(fd, buff, BUFFER_SIZE);
	while (*chars_readed > 0)
	{
		buff[*chars_readed] = '\0';
		tmp = ft_strjoin(rest, buff);
		free(rest);
		rest = tmp;
		if (ft_strchr(rest, '\n') != NULL || *chars_readed < BUFFER_SIZE)
			break ;
		*chars_readed = read(fd, buff, BUFFER_SIZE);
	}
	return (rest);
}

char	*init(int fd, char **buff, char **rest)
{
	if (fd == -2 && *rest)
	{
		free(*rest);
		*rest = NULL;
		return (NULL);
	}
	if (BUFFER_SIZE <= 0 || BUFFER_SIZE >= INT_MAX || fd < 0)
		return (NULL);
	*buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!*buff)
		return (NULL);
	if (*rest == NULL)
		*rest = ft_strjoin("", "");
	return (*rest);
}

char	*get_next_line(int fd)
{
	static char	*rest;
	char		*buff;
	char		*line;
	char		*tmp;
	ssize_t		chars_readed;

	if (!init(fd, &buff, &rest))
		return (NULL);
	rest = read_from_file(fd, rest, buff, &chars_readed);
	free(buff);
	rest = handle_errors(chars_readed, rest);
	if (rest == NULL)
		return (NULL);
	line = ft_line(rest);
	tmp = ft_rest(rest);
	free(rest);
	rest = tmp;
	return (line);
}
