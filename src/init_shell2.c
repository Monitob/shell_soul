/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernabe <jbernabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/24 19:36:21 by jbernabe          #+#    #+#             */
/*   Updated: 2014/03/27 12:27:51 by jbernabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "shell.h"

static void				init_key_control(t_shell *shell, t_letter **list_current)
{
	shell->data->line = NULL;
	shell->tcs->line_len = 0;
	*list_current = NULL;
}

static void				exec_type(t_shell **sh, t_letter **let, int type)
{
	void		(*key_control[5])(t_command **line, t_letter **) =
				{tercs_ascii, tercs_up, tercs_down, tercs_right, tercs_left};
	int			i;

	i = 0;
	while (i < 5)
	{
		if (i == typ`e)
		{
			key_control[type](&(*sh)->data , let);
			return ;
		}
		i++;
	}
}

void				show_prompt(t_shell **shell)
{
	int				i;
	char			**temp;
	int				len;
	extern char		**environ;

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
	ft_putstr((*shell)->pro->prompt);
	ft_putstr("\033[35m -> \033[0m");
	free(*temp);
	return ;
}

void			control_read(t_shell *root, t_letter *list_current,
						char key[8], int type)
{
	ft_memset(key, 0, 8);
	if (!list_current && type == -1)
	{
		cursor_control(list_current);
		show_prompt(&root);
	}
}

void			init_line(t_shell *root)
{
	int			type;
	t_letter	*list_current;
	char		key[8] = {0, 0, 0, 0, 0, 0, 0, 0};

	type = 0;
	init_key_control(root, &list_current);
	while (1)
	{
		type = read_key(key, 0);
		if (key[0] == 27 && key[1] == 0 && key[2] == 0)
			ft_memset(key, 0, 8);
		if (type > 0)
			exec_type(&root, &list_current, type);
		if ((key[2] == 0 && key[3] == 0) || type == -1)
		{
			if (type == -1 && list_current)
				ft_start_lexer(&root, &list_current);
			if (key[0] != 13)
				init_ascii(&list_current, key[0], &root);
		}
		control_read(root, list_current, key, type);
	}
}
