/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernabe <jbernabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/24 19:36:21 by jbernabe          #+#    #+#             */
/*   Updated: 2014/02/27 20:45:53 by jbernabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

#include <stdio.h> ////////

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
	shell->data->cmd_arg = NULL;
	shell->data->path = NULL;
	shell->data->line = NULL;
	shell->tcs->hist->str_tab = NULL;
	shell->tcs->hist->left = NULL;
	shell->tcs->line_len = 0;
	shell->tcs->index = 0;
}

static void		exec_type(t_shell *shell, int type, char key[8])
{
	void		(*key_control[4])(t_shell *, char [8]) = EXEC_INST; 
	int			i;

	i = 0;
	while(i < 4)
	{
		key_control[i](shell, key);
		if (i == type)
		{
			key_control[type](shell, key);
		}
		i++;
	}
}

int				init_line(t_shell *root)
{
	int			type;
	t_letter	*list_current;
	char		key[8] = {0, 0, 0, 0, 0, 0, 0, 0};

	type = 0;
	list_current = NULL;
	if (root)
	{
		init_key_control(root);
		while (!(key[0] == 27 && key[1] == 0))
		{
			ft_memset(key, 0, 8);
			read(0, key, BUFFER_R);
			type = set_type(key);
			if (type > -1)
				exec_type(root, type, key);
			if (key[2] == 0 && key[3] == 0)
			{
				init_ascii(&list_current, key[0]);
				display_list_test(list_current); //
			}
			key[2] = 0;
			key[3] = 0;
			key[5] = 0;
		}
	}
	return (0);
}
