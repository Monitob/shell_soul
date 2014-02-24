/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernabe <jbernabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/24 19:36:21 by jbernabe          #+#    #+#             */
/*   Updated: 2014/02/25 00:24:43 by jbernabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <stdio.h>

void		show_prompt(void)
{
	int		i;
	char	**temp;

	i = 0;
	while (strncmp(environ[i], "USER=", 5) != 0)
		i++;
	temp = ft_strsplit(environ[i], '=');
	temp++;
	ft_putstr(*temp);
	ft_putstr("\033[35m -> \033[0m");
	return ;
}

int				init_line(t_shell *root)
{
	t_command	line;
//	t_tercs		*list;

	ft_memset(line.buffer, 0, 5);
	if (root)
	{
		root->data->cmd_arg = NULL;
		ft_bzero(line.buffer, 5);
		while (!(line.buffer[0] == 27 && line.buffer[1] == 0
					&& line.buffer[2] == 0))
		{
			ft_bzero(line.buffer, 4);
			read(0, line.buffer, BUFFER_R);
			write(1, line.buffer, 1);
			if (line.buffer[2] == 0 && line.buffer[3] == 0)
			{
			//	list = cursor_control(line);
			//	root->data->arg_line = list_to_string(list);
			}
		/*	if (line.buffer[0] == 27 && line.buffer[1] == 91)
				ft_key_control(&list, line);*/
	/*		if (line.buffer[0] == 10)
				return (1);*/
			line.buffer[1] = 0;
			line.buffer[2] = 0;
			line.buffer[3] = 0;
		}
	}
	return (0);
}
/*
void		ft_key_control(t_tercs **list, t_command line)
{
	t_tercs	**aux;

	aux = list;
	if ((*list != NULL))
	{
		if ((line.buffer[2]) == 68)
		{
			if ((*aux)->previous == NULL)
				return ;
			tputs(tgetstr("le", NULL), 1, put_shell);
			*aux = (*aux)->previous;
		}
		if ((line.buffer[2]) == 67)
		{
			ft_putstr("dere");
			tputs(tgetstr("nd", NULL), 1, put_shell);
		}
		if ((line.buffer[2]) == 65)
			ft_putstr("arriba");
		if ((line.buffer[2]) == 66)
			ft_putstr("abajo");
	}
}
*/
