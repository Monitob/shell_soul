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

char	**parser(int ac, char **av, char **env)
{
	struct stat		check;
	char			**cmd_paths;
	char			*slash_cmd;
	char			*abs_path;
	char			*rm;
	int				ret;

	int				i;

	char 			*opt;
	int				o_end;

	o_end = opt_end(av);
	opt = opt_get(av);

	if (o_end > 1)
		opt = opt_get(av);

	if (av != NULL && stat(av[0], &check) == 0)
		buil_cmd(av[0], av, env);
	else if (av != NULL && ft_strcmp(av[0], "cd") == 0)
		buil_cd(ac, av, env, o_end, opt);
	else if (av != NULL && ft_strcmp(av[0], "setenv") == 0)
		env = buil_setenv(ac, av, env);
	else if (av != NULL && ft_strcmp(av[0], "unsetenv") == 0)
	env = buil_unsetenv(ac, av, env);
	else if (av != NULL && ft_strcmp(av[0], "env") == 0) //-option -i
		buil_env(ac, av, env, o_end);
	else if (av != NULL && ft_strncmp(av[0], "exit", 4) == 0)//csh
		_Exit(0);
	else
	{
		slash_cmd = ft_strjoin("/", av[0]);
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
				buil_cmd(abs_path, av, env); //mettre une condition pour l'env sans PATH ou PATH modifi'e
			else
			{
				ft_putstr("42sh: command not found: ");
				ft_putendl(av[0]);
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
			ft_putendl(av[0]);
		}
		free(rm);
	}
	return (env);
}