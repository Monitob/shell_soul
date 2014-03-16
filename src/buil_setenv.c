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

static char	**ft_addenv_var(char **msh_av, char **env, char option)
{
	char	**new_env;
	int		i;

	new_env = NULL;
	i = 0;
	if ((msh_av[1] = env_chkname(msh_av[1]))) //un truc pour afficher les caracteres speciaux
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
		new_env[i] = ft_strjoin(msh_av[1], "=");
		if (option)
			new_env[i] = ft_strjoin(new_env[i], msh_av[2]);
	}
	else
		ft_putendl("setenv: Syntax Error.");
	return (new_env);
}

/*
** csh
*/
char 		**buil_setenv(int ac, char **msh_av, char **env)
{
	int		i;

	i = 0;
	if (!msh_av[1])
		ft_puttab(env);
	else if (msh_av[1] && !msh_av[2]) //mieux vaut utiliser msh_ac!!!!!!!
	{
		if ((i = ft_tabidx(env, ft_strjoin(msh_av[1], "="), ft_strlen(msh_av[1]))) != -1)
			env[i] = ft_strjoin(msh_av[1], "=");
		else
			env = ft_addenv_var(msh_av, env, 0);
	}
	else if (msh_av[1] && msh_av[2] && !msh_av[3])
	{
		if ((i = ft_tabidx(env, ft_strjoin(msh_av[1], "="), ft_strlen(msh_av[1]))) != -1)
		{
			env[i] = ft_strjoin(msh_av[1], "=");
			env[i] = ft_strjoin(env[i], msh_av[2]);
		}
		else
			env = ft_addenv_var(msh_av, env, 1);
	}
	else if (ac > 3)
		ft_putendl("setenv: Too many arguments.");
	return (env);
}