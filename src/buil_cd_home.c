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

static void buil_cd_h_if(char **env, char *cpy_pwd, char *cpy_opwd, int opt_p)
{
	int		i;
	int		j;

	i = ft_tabidx(env, "PWD=", 4);
	j = ft_tabidx(env, "OLDPWD=", 7);
	if (chdir(env_rmname(env, "PWD=")))
	{
		ft_putstr("cd: no such file or directory: ");
		ft_putendl(env_rmname(env, "PWD="));
		env[i] = cpy_pwd;
		env[j] = cpy_opwd;
	}
	else if (opt_p == 1)
	{
		env[i] = ft_strjoin("PWD=", getcwd(NULL, 0));
		chdir(env_rmname(env, "PWD="));
	}
}

static void buil_cd_h_else(char **env, char *cpy_pwd, char *cpy_opwd, int opt_p)
{
	int		i;
	int		j;

	i = ft_tabidx(env, "PWD=", 4);
	j = ft_tabidx(env, "OLDPWD=", 7);
	if (chdir(env_rmname(env, "PWD=")))
	{
		ft_putstr("cd: no such file or directory: ");
		ft_putendl(env_rmname(env, "PWD="));
		env[i] = cpy_pwd;
		env[j] = cpy_opwd;
	}
	else if (opt_p == 1)
	{
		env[i] = ft_strjoin("PWD=", getcwd(NULL, 0));
		chdir(env_rmname(env, "PWD="));
	}
}

void		buil_cd_home(char **av, char **env, int opt_end, int opt_p)
{
	int		i;
	int		j;
	int		k;
	char	*cpy_pwd;
	char	*cpy_opwd;

	i = ft_tabidx(env, "PWD=", 4);
	j = ft_tabidx(env, "OLDPWD=", 7);
	k = ft_tabidx(env, "HOME=", 5);
	cpy_pwd = ft_strdup(env[i]);
	cpy_opwd = ft_strdup(env[j]);
	env_swap(&env[i], &env[j], 1);
	env_swap(&env[i], &env[k], 0);
	if (!av[opt_end] || !ft_strcmp(av[opt_end], "--"))
		buil_cd_h_if(env, cpy_pwd, cpy_opwd, opt_p);
	else
	{
		env[i] = ft_strjoin(env[i], ft_strsub(av[opt_end], 1,
			ft_strlen(av[opt_end])));
		buil_cd_h_else(env, cpy_pwd, cpy_opwd, opt_p);
	}
}
