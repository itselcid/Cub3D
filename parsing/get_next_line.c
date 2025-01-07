/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 15:12:38 by oessaadi          #+#    #+#             */
/*   Updated: 2025/01/07 14:01:55 by oel-moue         ###   ########.fr       */
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

char	*handle_errors(int chars_readed, char *rest)
{
	if (chars_readed == -1 || (chars_readed == 0
			&& (rest == NULL || *rest == '\0')))
	{
		free(rest);
		rest = NULL;
	}
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

char	*get_next_line(int fd)
{
	static char	*rest;
	char		*buff;
	char		*line;
	char		*tmp;
	ssize_t		chars_readed;

	if (BUFFER_SIZE <= 0 || BUFFER_SIZE >= INT_MAX || fd < 0)
		return (NULL);
	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	if (rest == NULL)
		rest = ft_strjoin("", "");
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
