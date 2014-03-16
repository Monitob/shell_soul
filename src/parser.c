/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flime <flime@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/16 13:10:24 by flime             #+#    #+#             */
/*   Updated: 2014/03/16 13:10:25 by flime            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	**parser(int ac, char **msh_av, char **env)
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
		buil_cmd(msh_av[0], msh_av, env);
	else if (msh_av != NULL && ft_strcmp(msh_av[0], "cd") == 0)
		buil_cd(ac, msh_av, env, opt_end, opt);
	else if (msh_av != NULL && ft_strcmp(msh_av[0], "setenv") == 0)
		env = buil_setenv(ac, msh_av, env);
	else if (msh_av != NULL && ft_strcmp(msh_av[0], "unsetenv") == 0)
	env = buil_unsetenv(ac, msh_av, env);
	else if (msh_av != NULL && ft_strcmp(msh_av[0], "env") == 0) //-option -i
		buil_env(ac, msh_av, env, opt_end);
	else if (msh_av != NULL && ft_strncmp(msh_av[0], "exit", 4) == 0)//csh
		_Exit(0);
	else
	{
		slash_cmd = ft_strjoin("/", msh_av[0]);
		rm = env_rmname(env, "PATH=");
		if (rm)
		{

			cmd_paths = ft_strsplit(rm, ':');
			while (*cmd_paths && \
				(ret = stat(abs_path = ft_strjoin(*cmd_paths, slash_cmd), &check)))
			{
				++cmd_paths;
			}
			if (ret == 0)
				buil_cmd(abs_path, msh_av, env); //mettre une condition pour l'env sans PATH ou PATH modifi'e
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