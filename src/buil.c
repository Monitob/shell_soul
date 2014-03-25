/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buil.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernabe <jbernabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/16 13:10:24 by flime             #+#    #+#             */
/*   Updated: 2014/03/25 05:48:14 by jbernabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	buil_cmd_slash(char **av, char **env, struct stat check)
{
	char			**cmd_paths;
	char			*slash_cmd;
	char			*abs_path;
	char			*rm;
	int				ret;

	slash_cmd = ft_strjoin("/", av[0]);
	rm = env_rmname(env, "PATH=");
	cmd_paths = ft_strsplit(rm, ':');
	while (*cmd_paths && (ret = stat(abs_path =
						ft_strjoin(*(cmd_paths++), slash_cmd), &check)))
		free(abs_path);
	if (rm && !ret)
	{
		buil_cmd(abs_path, av, env);/*att env sans PATH ou PATH modif*/
		free(slash_cmd);
		while (*cmd_paths)
			free(*(cmd_paths++));
	}
	else
	{
		ft_putstr("42sh: command not found: ");
		ft_putendl(av[0]);
	}
	free(rm);
}

static void		ft_push_parser(t_parser *new_el, t_parser **el_parser)
{
	t_parser	*temp;

	temp = *el_parser;
	if (temp == NULL)
	{
		*el_parser = new_el;
		return ;
	}
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	temp->next = new_el;
}

static int	ft_get_id(char *str)
{
	if (ft_strcmp(str, "|"))
		return (1);
	else if (ft_strcmp(str, ">"))
		return (2);
	else if (ft_strcmp(str, "<"))
		return (3);
	else if (ft_strcmp(str, ">>"))
		return (4);
	else if (ft_strcmp(str, ">>"))
		return (5);
	else if (ft_strcmp(str, "||"))
		return (6);
	else if (ft_strcmp(str, "&&"))
		return (7);
	else if (ft_strcmp(str, "&&"))
		return (8);
	else
		return (0);
}

void	ft_element_parser(char **av, t_parser **el_parser)
{
	int			i;
	t_parser	*new_el;

	i = 0;
	while (av[i] != NULL)
	{
		if (!(new_el = (t_parser *)malloc(sizeof(t_parser))))
			return ;
		new_el->cmd = av[i];
		new_el->id = ft_get_id(av[i]);
		if (el_parser == NULL)
			*el_parser = new_el;
		else
			ft_push_parser(new_el, el_parser);
		i++;
	}
}

char	**buil(t_shell **shell, int ac, char **av, char **env)
{
	struct stat		check;
	char			*opt;
	int				o_end;
	t_parser		*el_parser;


	el_parser = NULL;
	o_end = opt_end(av/*, "PL"*/);
	ft_putnbr(o_end);
	opt = opt_get(av);
	ft_putendl(opt);
	ft_element_parser(av, &el_parser);
	if (av != NULL && stat(av[0], &check) == 0)
		buil_cmd(av[0], av, env);
	else if (av != NULL && ft_strcmp(av[0], "cd") == 0)
		buil_cd(ac, av, env, o_end, opt);
	else if (av != NULL && ft_strcmp(av[0], "setenv") == 0)
		env = buil_setenv(ac, av, env);
	else if (av != NULL && ft_strcmp(av[0], "unsetenv") == 0)
		env = buil_unsetenv(ac, av, env);
	else if (av != NULL && ft_strcmp(av[0], "env") == 0)/* -option -i*/
		buil_env(ac, av, env, o_end);
	else if (av != NULL && ft_strncmp(av[0], "echo", 4) == 0)
		buil_echo(ac, av, env, opt);
	else if (av != NULL && ft_strncmp(av[0], "exit", 4) == 0)
		_Exit(0);
	else
		buil_cmd_slash(av, env, check);
	return (env);
	(void)shell;
}