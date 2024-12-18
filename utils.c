/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 12:52:38 by oel-moue          #+#    #+#             */
/*   Updated: 2024/12/18 23:32:57 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_strdup(char *src)
{
	int				i;
	char			*d;
	unsigned char	*s;
	size_t			j;

	j = ft_strlen(src);
	s = (unsigned char *)src;
	i = 0;
	d = malloc(j + 1);
	if (!d)
		return (0);
	while (s[i])
	{
		d[i] = s[i];
		i++;
	}
	d[i] = '\0';
	return (d);
}
int	ft_strlen_not_newline(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}
void	ft_memset(void *s, int c, size_t n)
{
	unsigned char *ptr;
	ptr = (unsigned char *)s;
	while (n--)
		*ptr++ = (unsigned char)c;
}
