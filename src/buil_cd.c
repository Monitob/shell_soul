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

static void			ft_run_cmd(const char *path, char **msh_av, char **env)
{
	pid_t			cmd;
	int				status;

/*	if (access(msh_av[0], X_OK) == -1)
	{
		ft_putstr("error: not access");
		return ;
	}*/
	if ((cmd = fork()) == -1)
	{
		ft_putstr("error: fork fail");
		return ;
	}
	if (cmd == 0)
	{
		execve(path, msh_av, env);
		exit(-1);
	}
	wait(&status);
}

/*static void ft_cd_home(char **msh_av, char **env)
  {
  int		i;
  char	*home;



  if (!msh_av)
  {
  if (!ft_strncmp(env[i], "PWD=", 4))
  env[i] = ft_strjoin("PWD=", old);
  chdir(ft_rm_env_name(home, "HOME="));
  }
//	chdir(ft_rm_env_name(old, "PWD="));
}*/


/*static void	ft_rm_env_last_dir(char **env)
  {
  int		i;

  i = 0;
  while (env[0][i])
  i++;
  while (env[0][i] != '/')
  i--;
  env[0] = ft_strndup(env[0], i);
  }*/

/*
 ** zsh
 ** cd ..,    // voir avec des .. dans le chemin // voir avec la source de fichier.
 */
/*static void ft_cd_dotdot(char **msh_av, char **env, int i, int j)
  {
  (void)msh_av;
  while (env[i])
  {
  if (!ft_strncmp(env[i], "PWD=", 4))
  break;
  i++;
  }
  while (env[j])
  {
  if (!ft_strncmp(env[j], "OLDPWD=", 7))
  break;
  j++;
  }
  ft_swap_env(&env[j], &env[i], 0);
  ft_rm_env_last_dir(&env[i]);
  chdir(ft_rm_env_name(env, "PWD="));
  }*/

/*
 ** zsh
 ** cd .,
 */
static void ft_cd_dot(char **msh_av, char **env, int i, int j)
{
	(void)msh_av;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PWD=", 4))
			break;
		i++;
	}
	while (env[j])
	{
		if (!ft_strncmp(env[j], "OLDPWD=", 7))
			break;
		j++;
	}
	ft_swap_env(&env[j], &env[i], 0);
	chdir(ft_rm_env_name(env, "PWD="));
}

/*
 ** sh
 ** cd -,
 */
static void ft_cd_sub(char **msh_av, char **env, int i, int j)
{
	(void)msh_av;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PWD=", 4))
			break;
		i++;
	}
	while (env[j])
	{
		if (!ft_strncmp(env[j], "OLDPWD=", 7))
			break;
		j++;
	}
	ft_swap_env(&env[i], &env[j], 1);
	chdir(ft_rm_env_name(env, "PWD="));
	ft_putendl(ft_rm_env_name(env, "PWD="));
}
/*
 ** zsh
 ** cd, cd ~, cd --
 */
static void ft_cd_home(char **msh_av, char **env, int i, int j, int k)
{
	(void)msh_av;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PWD=", 4))
			break;
		i++;
	}
	while (env[j])
	{
		if (!ft_strncmp(env[j], "OLDPWD=", 7))
			break;
		j++;
	}
	while (env[k])
	{
		if (!ft_strncmp(env[k], "HOME=", 5))
			break;
		k++;
	}
	ft_swap_env(&env[i], &env[j], 1);
	ft_swap_env(&env[i], &env[k], 0);
	chdir(ft_rm_env_name(env, "PWD="));
}

static void ft_cd(char **msh_av, char **env)
{
	// on peut initialiser OLDPWD ici;
	if (!msh_av[1] || !ft_strcmp(msh_av[1], "--"))
		ft_cd_home(msh_av, env, 0, 0, 0);
	else if (!ft_strcmp(msh_av[1], "-"))
		ft_cd_sub(msh_av, env, 0, 0);
	else if (!ft_strcmp(msh_av[1], "~"))
		ft_cd_home(msh_av, env, 0, 0, 0);
	else if (!ft_strcmp(msh_av[1], "."))
		ft_cd_dot(msh_av, env, 0, 0);
	/*	else if (!ft_strcmp(msh_av[1], ".."))
		ft_cd_dotdot(msh_av, env, 0, 0);*/
	else
	{
		if (chdir(msh_av[1]))
		{
			ft_putstr("cd: no such file or directory: ");
			ft_putendl(msh_av[1]);
		}
	}
}

/*
 **
 */
void	ft_parser(char **msh_av, char **env)
{
	struct stat		check;
	char			**cmd_paths;
	char			*slash_cmd;
	char			*abs_path;
	int				ret;

	if (msh_av != NULL && stat(msh_av[0], &check) == 0)
		ft_run_cmd(msh_av[0], msh_av, env);
	else if (msh_av != NULL && strcmp(msh_av[0], "cd") == 0)
		ft_cd(msh_av, env); // lancer cd; avec msh env
	else
	{
		slash_cmd = ft_strjoin("/", msh_av[0]);
		cmd_paths = ft_strsplit(ft_rm_env_name(env, "PATH="), ':');
		while (*cmd_paths && \
				(ret = stat(abs_path = ft_strjoin(*cmd_paths, slash_cmd), &check)))
			++cmd_paths;
		if (ret == 0)
			ft_run_cmd(abs_path, msh_av, env);
		else
		{
			ft_putstr("42sh: command not found: ");
			ft_putendl(msh_av[0]);
			TPUTS(cr);
		}
	}
}
