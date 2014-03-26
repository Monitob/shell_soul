/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buil_setenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flime <flime@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/16 12:37:30 by flime             #+#    #+#             */
/*   Updated: 2014/03/16 12:37:32 by flime            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char		**ft_addenv_var(char **av, char **env, char option)
{
	char	**new_env;
	int		i;

	new_env = NULL;
	i = 0;
	if ((av[1] = env_chkname(av[1])))
	{
		while (env[i])
			i++;
		new_env = (char **)malloc(sizeof(char*) * (i + 2));
		new_env[i + 1] = 0;
		i = 0;
		while (env[i])
		{
			new_env[i] = ft_strdup(env[i]);
			i++;
		}
		new_env[i] = ft_strjoin(av[1], "=");
		if (option)
			new_env[i] = ft_strjoin(new_env[i], av[2]);
	}
	else
		ft_putendl("setenv: Syntax Error.");
	return (new_env);
}

char			**buil_setenv(int ac, char **av, char **env)
{
	int		i;

	i = 0;
	if (!av[1])
		ft_puttab(env);
	else if (av[1] && !av[2])
	{
		if ((i = ft_tabidx(env, ft_strjoin(av[1], "="),
			ft_strlen(av[1]))) != -1)
			env[i] = ft_strjoin(av[1], "=");
		else
			env = ft_addenv_var(av, env, 0);
	}
	else if (av[1] && av[2] && !av[3])
	{
		if ((i = ft_tabidx(env, ft_strjoin(av[1], "="),
			ft_strlen(av[1]))) != -1)
			env[i] = ft_strjoin(ft_strjoin(av[1], "="), av[2]);
		else
			env = ft_addenv_var(av, env, 1);
	}
	else if (ac > 3)
		ft_putendl("setenv: Too many arguments.");
	return (env);
}
