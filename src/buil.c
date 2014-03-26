/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buil.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernabe <jbernabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/16 13:10:24 by flime             #+#    #+#             */
/*   Updated: 2014/03/26 05:45:28 by jbernabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void		ft_push_parser(t_parser *new_el, t_parser **el_parser)
{
	t_parser	*temp;

	if (*el_parser && new_el)
	{
		temp = *el_parser;
		while (temp->next != NULL)
		{
			dprintf(3, "ADD2 in while %p\n", temp->next);
			temp = temp->next;
		}
		temp->next = new_el;
	}
	else
	{
		dprintf(3, "add  null -> %p\n", el_parser);
		*el_parser = new_el;
	}
}

void			buil_cmd_slash(char **av, char **env, struct stat check)
{
	char			**cmd_paths;
	char			*slash_cmd;
	char			*rm;
	int				ret;

	slash_cmd = ft_strjoin("/", av[0]);
	rm = env_rmname(env, "PATH=");
	cmd_paths = ft_strsplit(rm, ':');
	while (*cmd_paths && (ret = stat(ft_strjoin(*(cmd_paths), slash_cmd)
		, &check)))
		free(ft_strjoin(*(cmd_paths++), slash_cmd));
	if (rm && !ret)
	{
		buil_cmd(ft_strjoin(*(cmd_paths), slash_cmd), av, env);
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

static int		ft_get_id(char *str)
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

void			ft_element_parser(char **av, t_parser **el_parser)
{
	int			i;
	t_parser	*new_el;

	i = 0;
	while (av[i] != NULL)
	{
		if (!(new_el = (t_parser *)malloc(sizeof(t_parser))))
			return ;
		new_el->cmd = av[i];
		dprintf(1, "cmd %s\n", new_el->cmd);
		new_el->id = ft_get_id(av[i]);
		new_el->next = NULL;
		if (el_parser == NULL)
		{
			dprintf(1, "el_parser NULL %p", *el_parser);
			*el_parser = new_el;
		}
		else
			ft_push_parser(new_el, el_parser);
		i++;
	}
}

char			**buil(int ac, char **av, char **env)
{
	struct stat		check;
	t_parser		*el_parser;

	el_parser = NULL;
	ft_element_parser(av, &el_parser);
	if (av != NULL && !stat(av[0], &check))
		buil_cmd(av[0], av, env);
	else if (av != NULL && !ft_strcmp(av[0], "cd"))
		buil_cd(ac, av, env, opt_get(av));
	else if (av != NULL && !ft_strcmp(av[0], "setenv"))
		env = buil_setenv(ac, av, env);
	else if (av != NULL && !ft_strcmp(av[0], "unsetenv"))
		env = buil_unsetenv(ac, av, env);
	else if (av != NULL && !ft_strcmp(av[0], "env"))
		buil_env(ac, av, env, opt_end(av));
	else if (av != NULL && !ft_strncmp(av[0], "echo", 4))
		buil_echo(ac, av, env, opt_get(av));
	else if (av != NULL && !ft_strncmp(av[0], "exit", 4))
		exit(0);
	else
		buil_cmd_slash(av, env, check);
	return (env);
}
