/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernabe <jbernabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/24 19:36:21 by jbernabe          #+#    #+#             */
/*   Updated: 2014/02/28 19:18:08 by jbernabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

#include <stdio.h> ////////

void			show_prompt(t_shell **shell)
{
	int			i;
	char		**temp;


	i = 0;
	while (strncmp(environ[i], "USER=", 5) != 0)
		i++;
	temp = ft_strsplit(environ[i], '=');
	temp++;
	(*shell)->prompt = (char *)malloc(sizeof(char) * ft_strlen(*temp));
	(*shell)->prompt = *temp;
	ft_putstr((*shell)->prompt);
	ft_putstr("\033[35m -> \033[0m");
	return ;
}

static void		init_key_control(t_shell *shell)
{
	shell->data->cmd_arg = NULL;
	shell->data->index = 0;
	shell->data->path = NULL;
	shell->data->line = NULL;
	shell->tcs->hist->str_tab = NULL;
	shell->tcs->hist->left = NULL;
	shell->tcs->line_len = 0;
}

static void		exec_type(t_command *line, t_letter *let, int type, char key[8])
{
	void		(*key_control[4])(EXE_PARAM) = EXEC_INST;
	int			i;

	i = 0;
	while(i < 4)
	{
		key_control[i](line, let, key);
		if (i == type)
		{
			key_control[type](line, let, key);
			return ;
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
			type = read_key(key, 0);
			if (type > 0)
				exec_type(root->data, list_current, type, key);
			if (key[2] == 0 && key[3] == 0 && key[0] != 10)
			{
				init_ascii(&list_current, key[0]);
				//	display_list_test(list_current); //
				char_to_string(&root->data, list_current, root->prompt);
				//ft_putendl(root->data->line);//
			}
			key[2] = 0;
			key[3] = 0;
			key[5] = 0;
		}
	}
	return (0);
}
