/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 10:46:52 by oel-moue          #+#    #+#             */
/*   Updated: 2024/11/24 16:25:06 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*read_fd(int fd, char *stock)
{
	char	*buffer;
	ssize_t	d;

	d = 1;
	buffer = malloc((size_t)BUFFER_SIZE + 1);
	if (buffer == NULL)
		return (NULL);
	while (!ft_strchr(stock, '\n') && d != 0)
	{
		d = read(fd, buffer, BUFFER_SIZE);
		if (d == -1)
			return (free(buffer), free(stock), NULL);
		buffer[d] = '\0';
		stock = ft_strjoin(stock, buffer);
		if (stock == NULL)
			return (free(buffer), NULL);
	}
	free(buffer);
	return (stock);
}

char	*ft_get_line(char *stock)
{
	char	*temp;
	int		i;
	int		j;

	if (stock == NULL || stock[0] == '\0')
		return (NULL);
	i = 0;
	while (stock[i] != '\0' && stock[i] != '\n')
		i++;
	temp = malloc(i + 2);
	if (temp == NULL)
	{
		free(stock);
		return (NULL);
	}
	i = 0;
	j = 0;
	while (stock[i] && stock[i] != '\n')
		temp[j++] = stock[i++];
	if (stock[i] == '\n')
		temp[j++] = stock[i];
	temp[j] = '\0';
	return (temp);
}

char	*rest(char *stock)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	if (stock == NULL)
		return (NULL);
	while (stock[i] && stock[i] != '\n')
		i++;
	if (stock[i] == '\0')
	{
		free(stock);
		return (NULL);
	}
	str = malloc(ft_strlen(stock) - i + 1);
	if (!str)
		return (free(stock), NULL);
	i++;
	j = 0;
	while (stock[i])
		str[j++] = stock[i++];
	str[j] = '\0';
	free(stock);
	return (str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stock;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	stock = read_fd(fd, stock);
	if (stock == NULL)
		return (NULL);
	line = ft_get_line(stock);
	stock = rest(stock);
	if (line == NULL)
		return (NULL);
	return (line);
}
