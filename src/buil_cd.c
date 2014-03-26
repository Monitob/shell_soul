/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buil_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernabe <jbernabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/28 13:31:45 by jbernabe          #+#    #+#             */
/*   Updated: 2014/03/13 19:40:30 by jbernabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <sys/wait.h>

static void		buil_cd_sub(char **av, char **env, int opt_p)
{
	int		i;
	int		j;

	(void)av;
	i = ft_tabidx(env, "PWD=", 4);
	j = ft_tabidx(env, "OLDPWD=", 7);
	env_swap(&env[i], &env[j], 1);
	if (opt_p == 1)
		env[i] = ft_strjoin("PWD=", getcwd(NULL, 0));
	chdir(env_rmname(env, "PWD="));
	ft_putendl(env_rmname(env, "PWD="));
}

static void		buil_cd_path(char **av, char **env, int opt_end, int opt_p)
{
	int		i;
	int		j;
	char	*sub1;

	i = ft_tabidx(env, "PWD=", 4);
	j = ft_tabidx(env, "OLDPWD=", 7);
	if (!ft_strncmp(av[opt_end], "/", 1))
	{
		if (opt_p == 0)
			sub1 = ft_strdup(av[opt_end]);
		else
			sub1 = getcwd(NULL, 0);
		env[i] = ft_strjoin("PWD=", sub1);
		free(sub1);
	}
	else
		env[i] = ft_strjoin("PWD=", getcwd(NULL, 0));
	chdir(env_rmname(env, "PWD="));
}

void			buil_cd(int ac, char **av, char **env, char *opt)
{
	char	opt_p;
	int		opt_e;

	opt_e = opt_end(av);
	opt_p = 0;
	if (strchr(opt, 'P'))
		opt_p = 1;
	if ((opt_chk(opt, "cd", "PL", "Usage: cd [-PL][-|<dir>].") == -1))
		ft_putendl("opt_chk");
	else if ((ac - opt_e) == 2)
		buil_cd_swap(av, env, opt_e, opt_p);
	else if ((ac - opt_e) < 2 && !av[opt_e])
		buil_cd_home(av, env, opt_e, opt_p);
	else if ((ac - opt_e) < 2 && !ft_strcmp(av[opt_e], "-"))
		buil_cd_sub(av, env, opt_p);
	else if ((ac - opt_e) < 2 && chdir(av[opt_e]))
	{
		ft_putstr("cd: no such file or directory: ");
		ft_putendl(av[opt_e]);
	}
	else if ((ac - opt_e) < 2)
		buil_cd_path(av, env, opt_e, opt_p);
	else
		ft_putendl("cd: too many arguments");
}
