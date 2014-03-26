/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buil_cd_home.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flime <flime@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 13:28:21 by flime             #+#    #+#             */
/*   Updated: 2014/03/26 13:28:24 by flime            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		buil_cd_home(char **av, char **env, int opt_end, int opt_p)
{
	int		i;
	int		j;
	int		k;
	char	*append;
	char	*cpy_pwd;
	char	*cpy_oldpwd;

	(void)opt_p;
	i = ft_tabidx(env, "PWD=", 4);
	j = ft_tabidx(env, "OLDPWD=", 7);
	k = ft_tabidx(env, "HOME=", 5);
	cpy_pwd = ft_strdup(env[i]);
	cpy_oldpwd = ft_strdup(env[j]);
	env_swap(&env[i], &env[j], 1);
	env_swap(&env[i], &env[k], 0);
	if (!av[opt_end] || !ft_strcmp(av[opt_end], "--"))
	{
		if (chdir(env_rmname(env, "PWD=")))
		{
			ft_putstr("cd: no such file or directory: ");
			ft_putendl(env_rmname(env, "PWD="));
			env[i] = cpy_pwd;
			env[j] = cpy_oldpwd;
		}
		else if (opt_p == 1)
		{
			env[i] = ft_strjoin("PWD=", getcwd(NULL, 0));
			chdir(env_rmname(env, "PWD="));
		}
	}
	else
	{
		append = ft_strsub(av[opt_end], 1, ft_strlen(av[opt_end]));
		env[i] = ft_strjoin(env[i], append);
		if (chdir(env_rmname(env, "PWD=")))
		{
			ft_putstr("cd: no such file or directory: ");
			ft_putendl(env_rmname(env, "PWD="));
			env[i] = cpy_pwd;
			env[j] = cpy_oldpwd;
		}
		else if (opt_p == 1)
		{
			env[i] = ft_strjoin("PWD=", getcwd(NULL, 0));
			chdir(env_rmname(env, "PWD="));
		}
	}
}
