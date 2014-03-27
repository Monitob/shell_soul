/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_swap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flime <flime@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/04 12:14:24 by flime             #+#    #+#             */
/*   Updated: 2014/03/27 11:30:40 by jbernabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "shell.h"

char		*env_getname(char *env)
{
	char	*env_name;
	int		len;

	len = 0;
	while (env[len - 1] != '=')
		len++;
	if (!(env_name = (char *)(malloc(sizeof(char) * (len + 1)))))
		return (NULL);
	len = 0;
	while (env[len - 1] != '=')
	{
		env_name[len] = env[len];
		len++;
	}
	env_name[len] = 0;
	return (env_name);
}

char		*env_getvalue(char *env)
{
	char	*env_value;
	int		i;
	int		len;

	if (env)
	{
		i = 0;
		while (env[i] != '=')
			i++;
		i++;
		len = 0;
		while (env[i + len])
			++len;
		if (!(env_value = (char *)(malloc(sizeof(char) * (len + 1)))))
			return (NULL);
		len = 0;
		while (env[i + len])
		{
			env_value[len] = env[i + len];
			len++;
		}
		env_value[len] = 0;
		return (env_value);
	}
	return (NULL);
}

void	env_swap(char **env1, char **env2, char c)
{
	char	*env1_cpy;

	env1_cpy = ft_strdup(env1[0]);
	env1[0] = ft_strjoin(env_getname(env1[0]), env_getvalue(env2[0]));
	if (c)
		env2[0] = ft_strjoin(env_getname(env2[0]), env_getvalue(env1_cpy));
}
