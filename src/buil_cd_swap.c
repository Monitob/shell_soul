/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buil_cd_swap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flime <flime@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 13:29:35 by flime             #+#    #+#             */
/*   Updated: 2014/03/27 12:34:24 by jbernabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void buil_cd_swap_err(char **av, int opt_end, int k)
{
	if (av[opt_end][k])
	{
		ft_putstr("cd: string not in pwd: ");
		ft_putendl(av[opt_end]);
	}
}

static void buil_cd_swap_2(int chdir_dup, char **env, int opt_p, char *cpy_pwd)
{
	char	*cpy_oldpwd;

	cpy_oldpwd = ft_strdup(env[ft_tabidx(env, "OLDPWD=", 7)]);
	if (chdir_dup)
	{
		ft_putstr("cd: no such file or directory: ");
		ft_putendl(env_rmname(env, "PWD="));
		env[ft_tabidx(env, "PWD=", 4)] = cpy_pwd;
		env[ft_tabidx(env, "OLDPWD=", 7)] = cpy_oldpwd;
	}
	else if (opt_p == 1)
	{
		env[ft_tabidx(env, "PWD=", 4)] = ft_strjoin("PWD=", getcwd(NULL, 0));
		env[ft_tabidx(env, "OLDPWD=", 7)] = cpy_oldpwd;
		chdir(env_rmname(env, "PWD="));
	}
}

void		buil_cd_swap(char **av, char **env, int opt_end, int opt_p)
{
	int		k;
	int		start;
	int		l;
	char	*cpy_pwd;

	cpy_pwd = ft_strdup(env[ft_tabidx(env, "PWD=", 4)]);
	l = 0;
	k = 0;
	while (env[ft_tabidx(env, "PWD=", 4)][l++] && av[opt_end][k])
	{
		k = 0;
		start = l;
		while (*(av[opt_end] + k++) == env[ft_tabidx(env, "PWD=", 4)][l] &&
			env[ft_tabidx(env, "PWD=", 4)][l] && av[opt_end][0])
			l++;
		if (!av[opt_end][k])
		{
			env[ft_tabidx(env, "PWD=", 4)] = ft_strjoin(ft_strjoin(ft_strndup
				(env[ft_tabidx(env, "PWD=", 4)], start)
				, av[opt_end + 1]), ft_strsub(cpy_pwd, l, ft_strlen(cpy_pwd)));
			buil_cd_swap_2(chdir(env_rmname(env, "PWD=")), env, opt_p, cpy_pwd);
			break ;
		}
	}
	buil_cd_swap_err(av, opt_end, k);
}
