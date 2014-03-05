/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernabe <jbernabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/24 19:36:21 by jbernabe          #+#    #+#             */
/*   Updated: 2014/03/05 17:14:27 by jbernabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

#include <stdio.h> ////////

void			show_prompt(t_shell **shell)
{
	int			i;
	char		**temp;
	int			len;

	i = 0;
	while (strncmp(environ[i], "USER=", 5) != 0)
		i++;
	temp = ft_strsplit(environ[i], '=');
	temp++;
	len = (int)ft_strlen(*temp);
	if (!((*shell)->pro->prompt = (char *)malloc(sizeof(char) * len)))
		return ;
	(*shell)->pro->prompt = *temp;
	(*shell)->pro->size_prompt = ft_strlen(*temp) + 4;
	TPUTS(bt);
	ft_putstr((*shell)->pro->prompt);
	ft_putstr("\033[35m -> \033[0m");
	return ;
}

static void		init_key_control(t_shell *shell)
{
	shell->data->line = NULL;
	shell->tcs->line_len = 0;

}

static void		exec_type(t_shell **sh, t_letter **let, int type)
{
	void		(*key_control[5])(EXE_PARAM) = EXEC_INST EXEC_INST2;
	int			i;

	i = 0;
	while(i < 5)
	{
		if (i == type)
		{
			key_control[type](&(*sh)->data , let);
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
				exec_type(&root, &list_current, type);
			if ((key[2] == 0 && key[3] == 0)|| type == -1) 
			{
				if (type == -1)
					ft_start_lexer(&root, &list_current);
				if (key[0] != 13)
					init_ascii(&list_current, key[0], &root);
			}
			key[2] = 0;
			key[3] = 0;
			key[5] = 0;
		}
	}
	return (0);
}
