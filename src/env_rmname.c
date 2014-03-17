/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_rmname.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flime <flime@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/16 13:43:25 by flime             #+#    #+#             */
/*   Updated: 2014/03/16 13:43:32 by flime            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*env_rmname(char **env, char *env_name)
{
	int				i;
	char			*env_value;
	int				env_len;

	i = 0;
	env_len = ft_strlen(env_name);
	while (env[i])
	{
		if (ft_strncmp(env[i], env_name, env_len) == 0)
		{
			env_value = ft_strsub(env[i], env_len, ft_strlen(env[i]) - env_len);
			return (env_value);
		}
		i++;
	}
	return (NULL);
}
