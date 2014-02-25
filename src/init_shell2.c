/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernabe <jbernabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/24 19:36:21 by jbernabe          #+#    #+#             */
/*   Updated: 2014/02/25 03:52:12 by jbernabe         ###   ########.fr       */
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
	int			i;
	void		(*fontions_list[6])(t_command *); 

	if (root)
	{
		i = -1;
		init_key_control(fontions_list, &line);
		root->data->cmd_arg = NULL;
		root->tcs->cursor = 0;
		while (!(line.buffer[0] == 27 && line.buffer[1] == 0
					&& line.buffer[2] == 0) && line.buffer[0] != 10)
		{
			ft_bzero(line.buffer, 8);
			read(0, line.buffer, BUFFER_R);
			/*here I do the verification of key and the I write*/
			while(fontions_list[++i])
				fontions_list[i](&line);
			write(1, line.buffer, 1);
			line.buffer[1] = 0;
			line.buffer[2] = 0;
			line.buffer[3] = 0;
		}
	}
	return (0);
}

void		init_key_control(void (*fontions_list[])(), t_command *key)
{
	fontions_list[0] = &tercs_up_hist;
	fontions_list[1] = &tercs_down_hist;
	fontions_list[2] = &tercs_insert;
	fontions_list[3] = &tercs_delete_hist;
	fontions_list[4] = &exec_line;
	fontions_list[5] = &tercs_edit_line;
	fontions_list[6] = NULL;
	ft_bzero(key->buffer, 8);
	ft_bzero(key->line, ft_strlen(key->line));
}
