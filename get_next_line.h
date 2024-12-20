/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessaadi <oessaadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 15:28:37 by oessaadi          #+#    #+#             */
/*   Updated: 2023/12/07 23:22:05 by oessaadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <limits.h>
#include"cub3d.h"

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 2
#endif

char *get_next_line(int fd);
char *ft_line(char *str);
char *ft_rest(char *str);
char *ft_strjoin(char *s1, char *s2);
size_t ft_strlen(const char *s);
char *ft_strncpy(char *dest, const char *src, size_t n);
char *ft_strchr(const char *s, int c);
char *handle_eof(int chars_readed, char *rest);
char *handle_line(char *rest);

#endif