/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernabe <jbernabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/24 19:36:21 by jbernabe          #+#    #+#             */
/*   Updated: 2014/02/26 13:33:25 by jbernabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <stdio.h>

void			show_prompt(void)
{
	int			i;
	char		**temp;

	i = 0;
	while (strncmp(environ[i], "USER=", 5) != 0)
		i++;
	temp = ft_strsplit(environ[i], '=');
	temp++;
	ft_putstr(*temp);
	ft_putstr("\033[35m -> \033[0m");
	return ;
}

static void		init_key_control(t_shell *shell)
{
	ft_bzero(shell->data->line, ft_strlen(shell->data->line));
	shell->data->cmd_arg = NULL;
	shell->tcs->cursor = 0;
}

static void		exec_type(t_shell *shell, int type, char key[8])
{
	void		(*key_control[5])(t_shell *, char [8]) = EXEC_INST; 
	int			i;

	i = 0;
	while(i < 5)
	{
		key_control[i](shell, key);
		if (i == type)
			key_control[i](shell, key);
		i++;
	}
}

int				init_line(t_shell *root)
{
	int			type;
	char		key[8] = {0, 0, 0, 0, 0, 0, 0, 0};

	type = 0;
	if (root)
	{
		init_key_control(root);
		while (!(key[0] == 27 && key[1] == 0
					&& key[2] == 0) && key[0] != 10)
		{
			read_key(key, 0);
			type = set_type(key);
			if (type > -1)
			{
				exec_type(root, type, key);
			}
			if (type == -1)
			{
				ft_putstr("enter");
				exit(0);
			}
			key[1] = 0;
			key[2] = 0;
			key[3] = 0;
		}
	}
	return (0);
}


