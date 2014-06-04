/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 19:40:57 by srabah-m          #+#    #+#             */
/*   Updated: 2014/03/27 19:42:39 by srabah-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doseshell.h"

char	*search_path(char **env)
{
	int	i;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	return (env[i]);
}

int		count_path(char *path)
{
	int	i;
	int	nb;

	i = 0;
	nb = 1;
	while (path[i])
	{
		if (path[i] == ':')
			nb++;
		i++;
	}
	return (nb);
}

int		my_strlen_path(char *path)
{
	int	i;

	i = 0;
	while (path[i] && path[i] != ':')
		i++;
	return (i);
}

char	**cpy_path(char *path_line)
{
	int		i;
	int		j;
	int		k;
	char	**path;

	i = 5;
	j = 0;
	path = malloc((count_path(path_line) + 1) * sizeof(char *));
	if (path == NULL)
		return ((char **)ft_error_null("Fail malloc()"));
	while (path_line[i])
	{
		k = 0;
		path[j] = malloc(my_strlen_path(path_line + i) + 2);
		if (path[j] == NULL)
			return ((char **)ft_error_null("Fail malloc()"));
		while (path_line[i] && path_line[i] != ':')
			path[j][k++] = path_line[i++];
		path[j][k++] = '/';
		path[j++][k] = '\0';
		if (path_line[i])
			i++;
	}
	path[j] = NULL;
	return (path);
}

char	**get_path(char **env)
{
	char	*path_line;

	path_line = search_path(env);
	if (!path_line)
		return ((char **)ft_error_null("No path"));
	return (cpy_path(path_line));
}
