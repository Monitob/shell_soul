/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernabe <jbernabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/24 19:36:21 by jbernabe          #+#    #+#             */
/*   Updated: 2014/02/26 11:29:53 by jbernabe         ###   ########.fr       */
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

int				init_line(t_shell *root)
{
	t_command	line;
	int			type;

	type = 0;
	if (root)
	{
		init_key_control(root, line.buffer);
		while (!(line.buffer[0] == 27 && line.buffer[1] == 0
					&& line.buffer[2] == 0) && line.buffer[0] != 10)
		{
			read_key(line.buffer, 0);
			type = set_type(line.buffer);
			if (type > -1)
			{
				exec_type(root, type, line.buffer);
			}
			if (type == -1)
			{
				ft_putstr("enter");
				exit(0);
			}
			write(1, line.buffer, 1);
			line.buffer[1] = 0;
			line.buffer[2] = 0;
			line.buffer[3] = 0;
		}
	}
	return (0);
}

static void		read_key(char key[8], int fd)
{
	ft_bzero(key, 9);
	read(0, key, BUFFER_R);
}

static void		init_key_control(t_shell *shell, t_command *key)
{

	ft_bzero(key->buffer, 8);
	ft_bzero(key->line, ft_strlen(key->line));
	shell->data->cmd_arg = NULL;
	shell->tcs->cursor = 0;
}

static void		exec_type(t_shell *shell, int type, char key[8])
{

	/*/!\ IL Y A 3 POUR L'INSTANT!, MAIS CA VA AUGMENTER EN RAISON DES NOMBRES DE
	 * FONTONS /!\*/
	void		(*key_control[4])(t_command *, char [8]) = EXEC_INST; 
	int			i;

	i = 0;
	while(i < 5)
	{
		key_control[i](shell, key[8]);
		if (i == type)
			key_control[i](shell, key);
		i++;
	}
}
