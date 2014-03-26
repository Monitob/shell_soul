/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flime <flime@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/04 12:14:24 by flime             #+#    #+#             */
/*   Updated: 2014/03/04 18:58:19 by flime            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "shell.h"
#include <stdlib.h>

char	*ft_get_env_name(char *env)
{
	char	*env_name;
	int		len;

	len = 0;
	while (env[len - 1] != '=')
		len++;
	env_name = (char *)(malloc(sizeof(char) * (len + 1)));
	len = 0;
	while (env[len - 1] != '=')
	{
		env_name[len] = env[len];
		len++;
	}
	env_name[len] = 0;
	return (env_name);
}

char	*ft_get_env_value(char *env)
{
	char	*env_value;
	int		i;
	int		len;

	i = 0;
	while (env[i] != '=')
		i++;
	i++;
	len = 0;
	while (env[i + len])
		++len;
	env_value = (char *)(malloc(sizeof(char) * (len + 1)));
	len = 0;
	while (env[i + len])
	{
		env_value[len] = env[i + len];
		len++;
	}
	env_value[len] = 0;
	return (env_value);
}

void	ft_swap_env(char **env1, char **env2, char c)
{
	char	*env1_cpy;

	env1_cpy = ft_strdup(env1[0]);
	env1[0] = ft_strjoin(ft_get_env_name(env1[0]),
		ft_get_env_value(env2[0]));
	if (c)
	{
		env2[0] = ft_strjoin(ft_get_env_name(env2[0]),
			ft_get_env_value(env1_cpy));
	}
}
