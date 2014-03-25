/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernabe <jbernabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/24 16:17:08 by jbernabe          #+#    #+#             */
/*   Updated: 2014/03/25 05:06:44 by jbernabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

#include <stdio.h>

int			main(void)
{
	t_shell	*root;

	root = NULL;
	root = init_shell(root);
	root->env = init_env();
	//get_path(&root->el_parser, root->env);
	show_prompt(&root);
	init_line(root);
	reset_term(root);
	return (0);
}

t_shell		*init_shell(t_shell *root)
{
	root = (t_shell *)malloc(sizeof(*root));
	root->data = (t_command *)malloc(sizeof(*(root->data)));
	root->tcs = (t_tercs *)malloc(sizeof(*(root->tcs)));
	root->pro = (t_prompt *)malloc(sizeof(*(root->pro)));
	root->line_h = (t_history *)malloc(sizeof(*(root->line_h)));
	if (root == NULL || root->data == NULL || root->tcs == NULL
			|| root->line_h == NULL
			|| root->pro == NULL)
		error_fd("Not enought memory", 2);
	root->tcs->tty_fd = set_fd();
	init_trcs(root->tcs);
	return (root);
}

char		**init_env(void)
{
	char	**env;
	int		i;
	int		len_env;

	len_env = ft_tab_len(environ);
	if (!(env = (char **)malloc(sizeof(char *) * (len_env + 1))))
		exit(-1);
	i = 0;
	while (i < len_env)
	{
		env[i] = (char *)malloc(sizeof(char) * (ft_strlen(environ[i]) + 1));
		if (env[i] == NULL)
			exit(-1);
		ft_strcpy(env[i], environ[i]);
		i++;
	}
	env[i] = NULL;
	return (env);
}
/*
void		get_path(t_parser **el_parser, char **env)
{
	char	**l_path;
	char	**antifuite;
	int		i;
	int		nb_path;
	char	*temp;

	i = 0;
	l_path = NULL;
	temp = NULL;
	if (!(*el_parser = (t_parser *)malloc(sizeof(t_parser))))
		exit(0);
	while (strncmp(env[i] , "PATH=", 5) != 0)
		i++;
	antifuite = ft_strsplit(env[i], '=');
	free(antifuite[0]);
	antifuite++;
	l_path = ft_strsplit(*antifuite, ':');
	free(antifuite[0]);
	nb_path = 0;
	while (l_path[nb_path])
	{
		temp = l_path[nb_path];
		l_path[nb_path] = ft_strjoin(l_path[nb_path], "/");
		free(temp);
		nb_path++;
	}
	l_path[nb_path] = NULL;
	(*el_parser)->path = l_path;
	(*el_parser)->next = NULL;
	(*el_parser)->cmd = NULL;
	(*el_parser)->id = 0;
}*/
