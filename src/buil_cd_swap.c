/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buil_cd_swap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flime <flime@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 13:29:35 by flime             #+#    #+#             */
/*   Updated: 2014/03/26 13:29:39 by flime            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		buil_cd_swap(char **av, char **env, int opt_end, int opt_p)
{
	int		i;
	int		j;
	int		k;
	int		start;
	int		l;
	char	*cpy_pwd;
	char	*cpy_oldpwd;

	i = ft_tabidx(env, "PWD=", 4);
	j = ft_tabidx(env, "OLDPWD=", 7);
	cpy_pwd = ft_strdup(env[i]);
	cpy_oldpwd = ft_strdup(env[j]);
	l = 0;
	k = 0;
	while (env[i][l] && av[opt_end][k])
	{
		k = 0;
		start = l;
		while (*(av[opt_end] + k++) == env[i][l] && env[i][l] && av[opt_end][0])
			l++;
		if (!av[opt_end][k])
		{
			env[i] = ft_strjoin(ft_strjoin(ft_strndup(env[i], start)
				, av[opt_end + 1]), ft_strsub(cpy_pwd, l, ft_strlen(cpy_pwd)));
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
				env[j] = cpy_oldpwd;
				chdir(env_rmname(env, "PWD="));
			}
			break ;
		}
		l++;
	}
	if (av[opt_end][k])
	{
		ft_putstr("cd: string not in pwd: ");
		ft_putendl(av[opt_end]);
	}
}
