/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 19:37:18 by srabah-m          #+#    #+#             */
/*   Updated: 2014/03/27 20:57:41 by srabah-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doseshell.h"

char	*re_malloc_or_init(char *str1, int size, int choix)
{
	char	*new_str;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (str1 == NULL)
		return (NULL);
	if (choix == 0)
	{
		new_str = malloc(size * 1000 + 1);
		if ((re_malloc_or_init(new_str, size * 1000, 1)) == NULL)
			return (NULL);
		while (str1[j])
			new_str[i++] = str1[j++];
		free(str1);
		return (new_str);
	}
	while (i <= size)
	{
		str1[i] = '\0';
		i++;
	}
	return (str1);
}

int		trim_mem(char *rest, char *line, int i, int j)
{
	while (rest[i] == '\0' && i != 1000)
		i++;
	while (i != 1000)
	{
		if (rest[i] == '\n' || rest[i] == '\0')
		{
			line[j] = '\0';
			rest[i] = '\0';
			return (1);
		}
		line[j] = rest[i];
		rest[i] = '\0';
		j++;
		i++;
	}
	return (0);
}

int		put_rest_in_line(char *rest, char *line)
{
	rest[1000] = -9;
	while (*line != '\0')
		line++;
	while (*rest != -9)
	{
		if (*rest == '\n' || *rest == '\0')
		{
			*line = '\0';
			*rest = '\0';
			while (*rest != -9)
				rest++;
			*rest = '\0';
			return (1);
		}
		*line = *rest;
		*rest = '\0';
		line++;
		rest++;
	}
	*rest = '\0';
	return (0);
}

char	*find_line(char *rest, char *line, int size, const int fd)
{
	int	i;

	if (trim_mem(rest, line, 0, 0) == 1)
		return (line);
	i = 0;
	while (read(fd, rest, 1000) > 0)
	{
		i++;
		if (i == 9)
		{
			i = 0;
			size += 10;
			if ((line = re_malloc_or_init(line, size, 0)) == NULL)
				return (NULL);
		}
		if (put_rest_in_line(rest, line) == 1)
			return (line);
	}
	if (line[0] != '\0')
		return (line);
	return (NULL);
}

char	*get_next_line(const int fd)
{
	static char	*rest;
	static int	one_time;
	static int	fd_cpy;
	char		*line;

	if (fd != fd_cpy)
		one_time = 0;
	if (one_time == 0)
	{
		rest = malloc(1000 + 1);
		if (re_malloc_or_init(rest, 1000, 1) == NULL)
			return (NULL);
		fd_cpy = fd;
		one_time++;
	}
	line = malloc(10 * 1000 + 1);
	if (re_malloc_or_init(line, 10 * 1000, 1) == NULL)
		return (NULL);
	return (find_line(rest, line, 10, fd));
}
