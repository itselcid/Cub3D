/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-moue <oel-moue@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 16:06:57 by oel-moue          #+#    #+#             */
/*   Updated: 2024/12/30 16:07:10 by oel-moue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int is_separator(char ch, char c)
{
    if (c == ' ')
    {
        if (ch == ' ' || ch == '\t')
            return (1);
        else
            return (0);
    }
    else
    {
        if (ch == c)
            return (1);
        else
            return (0);
    }
}

static int	count_words( char *s, char c)
{
	int	words;
	int	i;

	words = 0;
	i = 0;
	while (s != NULL && s[i])
	{
		if (!is_separator(s[i], c))
		{
			words++;
			while (s[i] && !is_separator(s[i], c))
				i++;
		}
		while (s[i] && is_separator(s[i], c))
			i++;
	}
	return (words);
}

static int	word_len( char *s, char c)
{
	int	len;

	len = 0;
	while (!is_separator(s[len], c) && s[len] != '\0')
	{
		len++;
	}
	return (len);
}

static char	**freemem(int i, char **result)
{
	while (i >= 0)
	{
		free(result[i]);
		i--;
	}
	free(result);
	return (NULL);
}

static char	*copy_word( char *s, char c)
{
	int		len;
	char	*word;
	int		j;

	len = word_len(s, c);
	word = (char *)malloc((len + 1) * sizeof(char));
	if (word == NULL)
		return (NULL);
	j = 0;
	while (j < len)
	{
		word[j] = s[j];
		j++;
	}
	word[len] = '\0';
	return (word);
}

char	**ft_split(char  *s, char c)
{
	int		i;
	char	**result;

	result = (char **)malloc((count_words(s, c) + 1) * sizeof(char *));
	if (result == NULL)
		return (NULL);
	i = 0;
	while (s != NULL && *s)
	{
		if (!is_separator(*s, c))
		{
			result[i] = copy_word(s, c);
			if (result[i] == NULL)
				return (freemem(i, result));
			s += word_len(s, c);
			i++;
		}
		else
			s++;
	}
	result[i] = NULL;
	return (result);
}
