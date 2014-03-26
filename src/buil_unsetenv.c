/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buil_unsetenv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flime <flime@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/16 13:04:19 by flime             #+#    #+#             */
/*   Updated: 2014/03/16 13:04:23 by flime            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char		**buil_unsetenv_del(char *av, char **env)
{
	int		j;
	int		k;
	char	**ret;

	j = 0;
	while (!ft_strncmp(env[j], av, ft_strlen(av)) && env[j])
		j++;
	if (env[j])
	{
		ret = (char **)malloc(sizeof(char *) * ft_tablen(env));
		j = 0;
		k = 0;
		while (*(env + j++))
		{
			if (ft_strncmp(env[j - 1], av, ft_strlen(av)))
				*(ret + k++) = env[j - 1];
		}
		ret[k] = 0;
		env = ret;
	}
	return (env);
}

char			**buil_unsetenv(int msh_ac, char **av, char **env)
{
	int		i;

	i = 1;
	if (msh_ac == 1)
		ft_putendl("unsetenv: Too few arguments.");
	else
	{
		while (av[i])
		{
			env = buil_unsetenv_del(av[i], env);
			i++;
		}
	}
	return (env);
}
