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

#include <stdio.h>

static char	*ft_rm_env_name(char **env, char *env_name)
{
	int				i;
	char			*env_value;
	int				env_len;

	i = 0;
	env_len = ft_strlen(env_name);
	while (env[i])
	{
		if (ft_strncmp(env[i], env_name, env_len) == 0)
		{
			env_value = ft_strsub(env[i], env_len, ft_strlen(env[i]) - env_len);
			return (env_value);
		}
		i++;
	}
	return (NULL);
}

static void	ft_run_cmd(const char *path, char **msh_av, char **env)
{
	pid_t			cmd;
	int				status;

	cmd = fork();
	if (cmd == 0)
	{
		execve(path, msh_av, env);
		exit(-1);
	}
	wait(&status);
}

/*
** Get env variable number, if variable is not found return -1
*/
static int	ft_getenv_num(char **env, char *name, int len)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], name, len))
			return (i);
		i++;
	}
	return (-1);
}

static void ft_cd_swap(char **msh_av, char **env, int opt_end, int opt_p)
{
	int		i;
	int		j;
	int		k;
	int		start;
	int		l;
	char	*cpy_pwd;
	char	*cpy_oldpwd;
	(void)opt_p;
	i = ft_getenv_num(env, "PWD=", 4);
	j = ft_getenv_num(env, "OLDPWD=", 7);
	cpy_pwd = ft_strdup(env[i]);
	cpy_oldpwd = ft_strdup(env[j]);
	// ft_swap_env(&env[i], &env[j], 1);
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
			if (chdir(ft_rm_env_name(env, "PWD=")))
			{
				ft_putstr("cd: no such file or directory: ");
				ft_putendl(ft_rm_env_name(env, "PWD="));
				env[i] = cpy_pwd;
				env[j] = cpy_oldpwd;
			}
			else if (opt_p == 1)
			{
				env[i] = ft_strjoin("PWD=", getcwd(NULL, 0));
				env[j] = cpy_oldpwd;
				chdir(ft_rm_env_name(env, "PWD="));
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
static void ft_cd_sub(char **msh_av, char **env, int opt_p)
{
	int		i;
	int		j;

	(void)msh_av;
	i = ft_getenv_num(env, "PWD=", 4);
	j = ft_getenv_num(env, "OLDPWD=", 7);
	ft_swap_env(&env[i], &env[j], 1);
	if (opt_p == 1)
		env[i] = ft_strjoin("PWD=", getcwd(NULL, 0));
	chdir(ft_rm_env_name(env, "PWD="));
	ft_putendl(ft_rm_env_name(env, "PWD="));
}

/*
** zsh
** cd, cd ~, cd --
*/
static void ft_cd_home(char **msh_av, char **env, int opt_end, int opt_p)
{
	int		i;
	int		j;
	int		k;
	char	*append;
	char	*cpy_pwd;
	char	*cpy_oldpwd;

	(void)opt_p;
	i = ft_getenv_num(env, "PWD=", 4);
	j = ft_getenv_num(env, "OLDPWD=", 7);
	k = ft_getenv_num(env, "HOME=", 5);
	cpy_pwd = ft_strdup(env[i]);
	cpy_oldpwd = ft_strdup(env[j]);
	ft_swap_env(&env[i], &env[j], 1);
	ft_swap_env(&env[i], &env[k], 0);
	if (!msh_av[opt_end] || !ft_strcmp(msh_av[opt_end], "--") || !ft_strcmp(msh_av[opt_end], "~"))//probleme avec le tild
	{
		if (chdir(ft_rm_env_name(env, "PWD=")))
		{
			ft_putstr("cd: no such file or directory: ");
			ft_putendl(ft_rm_env_name(env, "PWD="));
			env[i] = cpy_pwd;
			env[j] = cpy_oldpwd;
		}
		else if (opt_p == 1)
		{
			env[i] = ft_strjoin("PWD=", getcwd(NULL, 0));
			chdir(ft_rm_env_name(env, "PWD="));
		}
	}
	else if (ft_strncmp(msh_av[opt_end], "~/", 2)) //tild dans le parseur.
	{

		env[i] = ft_rm_env_name(env, "HOME=");
		k = 0;
		while (env[i][k])
			k++;
		while (k > 0 && env[i][k] != '/')
			k--;
		k++;
		env[i] = ft_strndup(env[i], k);
		env[i] = ft_strjoin("PWD=", env[i]);
		env[i] = ft_strjoin(env[i], ft_strsub(msh_av[opt_end], 1, ft_strlen(msh_av[opt_end])));
		if (chdir(ft_rm_env_name(env, "PWD=")))
		{
			ft_putendl("42sh: no such user or named directory: dgsdf");
			env[i] = cpy_pwd;
			env[j] = cpy_oldpwd;
		}
		else if (opt_p == 1)
		{
			env[i] = ft_strjoin("PWD=", getcwd(NULL, 0));
			chdir(ft_rm_env_name(env, "PWD="));
		}
	}
	else
	{
		append = ft_strsub(msh_av[opt_end], 1, ft_strlen(msh_av[opt_end]));
		env[i] = ft_strjoin(env[i], append);
		if (chdir(ft_rm_env_name(env, "PWD=")))
		{
			ft_putstr("cd: no such file or directory: ");
			ft_putendl(ft_rm_env_name(env, "PWD="));
			env[i] = cpy_pwd;
			env[j] = cpy_oldpwd;
		}
		else if (opt_p == 1)
		{
			env[i] = ft_strjoin("PWD=", getcwd(NULL, 0));
			chdir(ft_rm_env_name(env, "PWD="));
		}
	}
}
/*
** zsh
** cd ., cd .., cd ./../../././., cd /path/to/lol
*/
static void ft_cd_path(char **msh_av, char **env, int opt_end, int opt_p)
{
	int		i;
	int		j;
	char	*sub1;

	i = ft_getenv_num(env, "PWD=", 4);
	j = ft_getenv_num(env, "OLDPWD=", 7);
	ft_swap_env(&env[i], &env[j], 1);
	if (!ft_strncmp(msh_av[opt_end], "/", 1))
	{
		if (opt_p == 0)
			sub1 = ft_strdup(msh_av[opt_end]);
		else
			sub1 = getcwd(NULL, 0);
		env[i] = ft_strjoin("PWD=", sub1);
		free(sub1);
	}
	else
		env[i] = ft_strjoin("PWD=", getcwd(NULL, 0));
	chdir(ft_rm_env_name(env, "PWD=")); //tester la valeur de retour; voir si chdir est inutile vu qu' on en fait un avant;
}

static void ft_cd(int ac, char **msh_av, char **env, int opt_end, char *opt)
{
	char	usage[] = "Usage: cd [-PL][-|<dir>]."; // ce message n'existe pas sous zsh.
	char	opt_p;

	opt_p = 0;
	if (strchr(opt, 'P'))
		opt_p = 1;
	if ((opt_chk(opt, "cd", "PL", usage) == -1))
		/*ft_putendl(opt_chk(opt, "cd", "PL", usage))*/;
	else if ((ac - opt_end) == 2)
	{
		ft_cd_swap(msh_av, env, opt_end, opt_p);
	}
	else if(ac - opt_end < 2)
	{
		if (!msh_av[opt_end]  || !ft_strncmp(msh_av[opt_end], "~", 1))
			ft_cd_home(msh_av, env, opt_end, opt_p);
		else if (!ft_strcmp(msh_av[opt_end], "-")) // gerer les options
			ft_cd_sub(msh_av, env, opt_p);
		else if (chdir(msh_av[opt_end]))
		{
				ft_putstr("cd: no such file or directory: ");
				ft_putendl(msh_av[opt_end]);
		}
		else
			ft_cd_path(msh_av, env, opt_end, opt_p);
	}
	else
		ft_putendl("cd: too many arguments");
}

/*
** csh
*/
static void ft_env(int ac, char **msh_av, char **env, int opt_end)
{
	//option -i -iiiiiiiiiiii
	(void)ac;
	(void)msh_av;
	(void)opt_end;
	ft_puttab(env);
}

/*
** faire un str ft_tabjoin
*/
static char	**ft_addenv_var(char **msh_av, char **env, char option)
{
	char	**new_env;
	int		i;

	new_env = NULL;
	i = 0;
	if ((msh_av[1] = ft_chkenv_name(msh_av[1]))) //un truc pour afficher les caracteres speciaux
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
static char **ft_setenv(int ac, char **msh_av, char **env)
{
	int		i;

	(void)ac;
	i = 0;
	if (!msh_av[1])
		ft_puttab(env);
	else if (msh_av[1] && !msh_av[2]) //mieux vaut utiliser msh_ac!!!!!!!
	{
		if ((i = ft_getenv_num(env, ft_strjoin(msh_av[1], "="), ft_strlen(msh_av[1]))) != -1)
			env[i] = ft_strjoin(msh_av[1], "=");
		else
			env = ft_addenv_var(msh_av, env, 0);
	}
	else if (msh_av[1] && msh_av[2] && !msh_av[3])
	{
		if ((i = ft_getenv_num(env, ft_strjoin(msh_av[1], "="), ft_strlen(msh_av[1]))) != -1)
		{
			env[i] = ft_strjoin(msh_av[1], "=");
			env[i] = ft_strjoin(env[i], msh_av[2]);
		}
		else
			env = ft_addenv_var(msh_av, env, 1);
	}
	else
		ft_putendl("setenv: Too many arguments.");
	return (env);
}

/*
** csh
*/
static char **ft_unsetenv(int msh_ac, char **msh_av, char **env)
{
	int		i;
	int		j;
	int		k;
	char	**ret;

	i = 1;
	if (msh_ac == 1)
		ft_putendl("unsetenv: Too few arguments.");
	else
	{
		while (msh_av[i])
		{
			j = 0;
			while (!ft_strncmp(env[j], msh_av[i], ft_strlen(msh_av[i])) && env[j])
				j++;
			if (env[j])
			{
				ret = (char **)malloc(sizeof(char *) * ft_tablen(env));
				j = 0;
				k = 0;
				while (env[j])
				{
					if (ft_strncmp(env[j], msh_av[i], ft_strlen(msh_av[i])))
					{
						ret[k] = env[j];
						k++;
					}
					j++;
				}
				ret[k] = 0;
				env = ret;
			}
			i++;
		}
	}
	return (env);
}

/*
**
*/

char	**ft_parser(int ac, char **msh_av, char **env)
{
	struct stat		check;
	char			**cmd_paths;
	char			*slash_cmd;
	char			*abs_path;
	char			*rm;
	int				ret;

	int				i;

	int				opt_end;
	char 			*opt;

	opt = opt_get(msh_av);
	opt_end = 1; //a verifier si 1 ou 2;
	while (msh_av[opt_end] && !(msh_av[opt_end][0] != '-' ||
			(msh_av[opt_end][0] == '-' && (msh_av[opt_end][1] == 0 || msh_av[opt_end][1] == '-'))))
		opt_end++;
	if (msh_av[opt_end] && !ft_strncmp(msh_av[opt_end], "--", 2))
		opt_end++;
	if (opt_end > 1)
		opt = opt_get(msh_av);

	if (msh_av != NULL && stat(msh_av[0], &check) == 0)
		ft_run_cmd(msh_av[0], msh_av, env);
	else if (msh_av != NULL && ft_strcmp(msh_av[0], "cd") == 0)
		ft_cd(ac, msh_av, env, opt_end, opt);
	else if (msh_av != NULL && ft_strcmp(msh_av[0], "setenv") == 0)
		env = ft_setenv(ac, msh_av, env);
	else if (msh_av != NULL && ft_strcmp(msh_av[0], "unsetenv") == 0)
	env = ft_unsetenv(ac, msh_av, env);
	else if (msh_av != NULL && ft_strcmp(msh_av[0], "env") == 0) //-option -i
		ft_env(ac, msh_av, env, opt_end);
	else if (msh_av != NULL && ft_strncmp(msh_av[0], "exit", 4) == 0)//csh
		_Exit(0);
	else
	{
		slash_cmd = ft_strjoin("/", msh_av[0]);
		rm = ft_rm_env_name(env, "PATH=");
		if (rm)
		{

			cmd_paths = ft_strsplit(rm, ':');
			while (*cmd_paths && \
				(ret = stat(abs_path = ft_strjoin(*cmd_paths, slash_cmd), &check)))
			{
				++cmd_paths;
			}
			if (ret == 0)
				ft_run_cmd(abs_path, msh_av, env); //mettre une condition pour l'env sans PATH ou PATH modifi'e
			else
			{
				ft_putstr("42sh: command not found: ");
				ft_putendl(msh_av[0]);
			}
			free(abs_path);
			free(slash_cmd);
			i = 0;
			while (cmd_paths[i])
			{
				free(cmd_paths[i]);
				i++;
			}
		}
		else
		{
			ft_putstr("42sh: command not found: ");
			ft_putendl(msh_av[0]);
		}
		free(rm);
	}
	return (env);
}