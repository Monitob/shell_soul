/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flime <flime@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/16 13:10:24 by flime             #+#    #+#             */
/*   Updated: 2014/03/16 19:58:12 by jbernabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include "shell.h"

char	**parser(int ac, char **av, char **env)
{
	struct stat		check;


	if (av)
	{
		if (stat(av[0], &check) == 0)
			buil_cmd(av[0], av, env);
		else if (!ft_strcmp(av[0], "cd"))
			buil_cd(ac, av, env, o_end, opt);
		else if (!ft_strcmp(av[0], "setenv"))
			env = buil_setenv(ac, av, env);
		else if (!ft_strcmp(av[0], "unsetenv"))
			env = buil_unsetenv(ac, av, env);
		else if (!ft_strcmp(av[0], "env"))
			buil_env(ac, av, env, o_end);
		else if (!ft_strncmp(av[0], "echo", 4))
			buil_echo(ac, av, env, opt);
		else if (av && !ft_strncmp(av[0], "exit", 4))
			_Exit(0);
		else
		{
			int		i;
			int		ret;
			char	*rm;
			char	*abs_path;
			char	*slash_cmd;
			char	**cmd_paths;
			char	*opt;
			int		o_end;

			o_end = opt_end(av);
			opt = opt_get(av);
			slash_cmd = ft_strjoin("/", av[0]);
			rm = env_rmname(env, "PATH=");
			if (rm)
			{
				abs_path = ft_strjoin(*cmd_paths, slash_cmd);
				cmd_paths = ft_strsplit(rm, ':');
				while (*cmd_paths && \
					(ret = stat(abs_path, &check)))
					++cmd_paths;
				if (!ret)
					buil_cmd(abs_path, av, env);
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
	}
	return (env);
}
*/