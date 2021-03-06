/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernabe <jbernabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/24 16:17:08 by jbernabe          #+#    #+#             */
/*   Updated: 2014/03/27 12:30:13 by jbernabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "shell.h"

static void		ft_mega_memset(t_shell *root)
{
	ft_memset(root->data, 0, sizeof(t_shell));
	ft_memset(root->tcs, 0, sizeof(*(root->tcs)));
	ft_memset(root->pro, 0, sizeof(*(root->pro)));
	ft_memset(root->line_h, 0, sizeof(*(root->line_h)));
}

int				main(void)
{
	t_shell		*root;

	root = NULL;
	root = init_shell(root);
	root->env = init_env();
	show_prompt(&root);
	init_line(root);
	reset_term(root);
	return (0);
}

t_shell			*init_shell(t_shell *root)
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
	ft_mega_memset(root);
	root->tcs->tty_fd = set_fd();
	init_trcs(root->tcs);
	return (root);
}

char			**init_env(void)
{
	extern char	**environ;
	char		**env;
	int			i;
	int			len_env;

	len_env = ft_tab_len(environ);
	if (!(env = (char **)malloc(sizeof(char *) * (len_env + 1))))
		exit(-1);
	i = 0;
	while (i < len_env)
	{
		if (!(env[i] = (char *)malloc(sizeof(char) *
						(ft_strlen(environ[i]) + 1))))
			return (NULL);
		if (env[i] == NULL)
			exit(-1);
		ft_strcpy(env[i], environ[i]);
		i++;
	}
	env[i] = NULL;
	return (env);
}
