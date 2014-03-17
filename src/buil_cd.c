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
#include <unistd.h>
#include <sys/wait.h>

static void		buil_cd_swap(char **av, char **env, int opt_end, int opt_p)
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
	l = (k = 0);
	while (env[i][l] && av[opt_end][k])
	{
		k = 0;
		start = l;
		while (*(av[opt_end] + k++) == env[i][l] && env[i][l] && av[opt_end][0])
			l++;
		if (!av[opt_end][k])
		{
			env[i] = ft_strjoin(ft_strndup(env[i], start), av[opt_end + 1]);
			env[i] = ft_strjoin(env[i], ft_strsub(cpy_pwd, l, ft_strlen(cpy_pwd)));
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

/*
** sh
** cd -,
*/
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

/*
** zsh
** cd, cd --
*/
static void		buil_cd_home(char **av, char **env, int opt_end, int opt_p)
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
	if (!av[opt_end] || !ft_strcmp(av[opt_end], "--")) /*probleme avec le tild*/
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
/*
** zsh
** cd ., cd .., cd ./../../././., cd /path/to/lol, ~, ~/
*/
static void		buil_cd_path(char **av, char **env, int opt_end, int opt_p)/*a revoir, les pwd ne marchent pas*/
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
	{
		env[i] = ft_strjoin("PWD=", getcwd(NULL, 0));//chemin absolue a revoir;
		ft_putendl(env[i]);
	}
	chdir(env_rmname(env, "PWD=")); /*tester la valeur de retour; voir si chdir est inutile vu qu' on en fait un avant;*/
}

void			buil_cd(int ac, char **av, char **env, int opt_end, char *opt)
{
	char	usage[] = "Usage: cd [-PL][-|<dir>].";/*ce message n'existe pas sous zsh.*/
	char	opt_p;

	opt_p = 0;
	if (strchr(opt, 'P')) //ternaire
		opt_p = 1;
	if ((opt_chk(opt, "cd", "PL", usage) == -1))
		ft_putendl("opt_chk");
	else if ((ac - opt_end) == 2)
		buil_cd_swap(av, env, opt_end, opt_p);
	else if ((ac - opt_end) < 2 && !av[opt_end])
		buil_cd_home(av, env, opt_end, opt_p);
	else if ((ac - opt_end) < 2 && !ft_strcmp(av[opt_end], "-"))
			buil_cd_sub(av, env, opt_p);
	else if ((ac - opt_end) < 2 && chdir(av[opt_end]))
	{
		ft_putstr("cd: no such file or directory: ");
		ft_putendl(av[opt_end]);
	}
	else if ((ac - opt_end) < 2)
			buil_cd_path(av, env, opt_end, opt_p);
	else
		ft_putendl("cd: too many arguments");
}
