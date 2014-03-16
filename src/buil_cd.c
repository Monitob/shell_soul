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

#include <stdio.h> //Attention

static void buil_cd_swap(char **msh_av, char **env, int opt_end, int opt_p)
{
	int		i;
	int		j;
	int		k;
	int		start;
	int		l;
	char	*cpy_pwd;
	char	*cpy_oldpwd;
	(void)opt_p;
	i = ft_tabidx(env, "PWD=", 4);
	j = ft_tabidx(env, "OLDPWD=", 7);
	cpy_pwd = ft_strdup(env[i]);
	cpy_oldpwd = ft_strdup(env[j]);
	l = 0;
	k = 0;
	while (env[i][l] && msh_av[opt_end][k])
	{
		k = 0;
		start = l;
		while (msh_av[opt_end][k] == env[i][l] && env[i][l] && msh_av[opt_end][0])
		{
			k++;
			l++;
		}
		if (!msh_av[opt_end][k])
		{
			env[i] = ft_strndup(env[i], start);
			env[i] = ft_strjoin(env[i], msh_av[opt_end + 1]);
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
	if (msh_av[opt_end][k])
	{
		ft_putstr("cd: string not in pwd: ");
		ft_putendl(msh_av[opt_end]);
	}
}

/*
** sh
** cd -,
*/
static void buil_cd_sub(char **msh_av, char **env, int opt_p)
{
	int		i;
	int		j;

	(void)msh_av;
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
** cd, cd ~, cd --
*/
static void buil_cd_home(char **msh_av, char **env, int opt_end, int opt_p)
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
	if (!msh_av[opt_end] || !ft_strcmp(msh_av[opt_end], "--") || !ft_strcmp(msh_av[opt_end], "~"))//probleme avec le tild
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
	else if (ft_strncmp(msh_av[opt_end], "~/", 2)) //tild dans le parseur.
	{

		env[i] = env_rmname(env, "HOME=");
		k = 0;
		while (env[i][k])
			k++;
		while (k > 0 && env[i][k] != '/')
			k--;
		k++;
		env[i] = ft_strndup(env[i], k);
		env[i] = ft_strjoin("PWD=", env[i]);
		env[i] = ft_strjoin(env[i], ft_strsub(msh_av[opt_end], 1, ft_strlen(msh_av[opt_end])));
		if (chdir(env_rmname(env, "PWD=")))
		{
			ft_putendl("42sh: no such user or named directory: dgsdf");
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
		append = ft_strsub(msh_av[opt_end], 1, ft_strlen(msh_av[opt_end]));
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
** cd ., cd .., cd ./../../././., cd /path/to/lol
*/
static void buil_cd_path(char **msh_av, char **env, int opt_end, int opt_p)
{
	int		i;
	int		j;
	char	*sub1;

	i = ft_tabidx(env, "PWD=", 4);
	j = ft_tabidx(env, "OLDPWD=", 7);
	env_swap(&env[i], &env[j], 1);
	if (!ft_strncmp(msh_av[opt_end], "/", 1))
	{
		if (opt_p == 0)
		{
			sub1 = ft_strdup(msh_av[opt_end]);
		}
		else
		{
			sub1 = getcwd(NULL, 0);
		}
		env[i] = ft_strjoin("PWD=", sub1);
		free(sub1);
	}
	else
	{
		env[i] = ft_strjoin("PWD=", getcwd(NULL, 0));
	}
	chdir(env_rmname(env, "PWD=")); //tester la valeur de retour; voir si chdir est inutile vu qu' on en fait un avant;
}

void 		buil_cd(int ac, char **msh_av, char **env, int opt_end, char *opt)
{
	char	usage[] = "Usage: cd [-PL][-|<dir>]."; // ce message n'existe pas sous zsh.
	char	opt_p;

	opt_p = 0;
	if (strchr(opt, 'P'))
		opt_p = 1;
	if ((opt_chk(opt, "cd", "PL", usage) == -1))
		;
	else if ((ac - opt_end) == 2)
		buil_cd_swap(msh_av, env, opt_end, opt_p);
	else if(ac - opt_end < 2)
	{
		if (!msh_av[opt_end]  || !ft_strncmp(msh_av[opt_end], "~", 1))
		{
			buil_cd_home(msh_av, env, opt_end, opt_p);
			ft_putstr("4");
		}
		else if (!ft_strcmp(msh_av[opt_end], "-"))
		{
			ft_putstr("3");
			buil_cd_sub(msh_av, env, opt_p);
		}
		else if (chdir(msh_av[opt_end]))
		{
			ft_putstr("4");
			ft_putstr("cd: no such file or directory: ");
			ft_putendl(msh_av[opt_end]);
		}
		else
		{
			ft_putstr("5");
			buil_cd_path(msh_av, env, opt_end, opt_p);
		}
	}
	else
		ft_putendl("cd: too many arguments");
}
