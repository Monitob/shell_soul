/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_verify.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernabe <jbernabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/03 19:51:16 by jbernabe          #+#    #+#             */
/*   Updated: 2014/03/25 02:37:18 by jbernabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <unistd.h>

void	cursor_control2(t_letter *list_let)
{
	int		i;

	i = 0;
	TPUTS(bt);
	while (i < ft_list_len(list_let))
	{
		TPUTS(le);
		i++;
	}
	TPUTS(bt);
}

void	cursor_control(t_letter *list_let)
{
	int		i;

	i = 0;
	TPUTS(bt);
	TPUTS(do);
	while (i < ft_list_len(list_let))
	{
		TPUTS(le);
		i++;
	}
	TPUTS(bt);
}

void	ft_start_lexer(t_shell **shell, t_letter **list_let)
{
	t_history	*hist;

	hist = NULL;
	if (!shell || !list_let)
		return ;
	if (list_let)
	{
		init_history(*list_let, &hist);
		char_to_string(&(*shell)->data, *list_let);
		TPUTS(bt);
		cursor_control(*list_let);
		tcsetattr((*shell)->tcs->tty_fd, TCSADRAIN,
				&((*shell)->tcs->term_save));
		lex_verify(shell, list_let);
		tcsetattr((*shell)->tcs->tty_fd, TCSADRAIN, &((*shell)->tcs->term_fd));
		cursor_control2(*list_let);
		show_prompt(shell);
		ft_delete_list(list_let);
		init_line(*shell);
		free((*shell)->data->line);
	}
}

void	lex_verify(t_shell **shell, t_letter **let)
{
	char	**msh_av;

	if ((*shell)->data || (*let)->letter)
	{
		if ((msh_av = ft_strsplit_space((*shell)->data->line)) == 0)
			return ;
		if (msh_av[0] != NULL)
		{
			ft_putendl("lex");
			if (parse_tilde(msh_av, (*shell)->env) != -1)
				(*shell)->env = buil(ft_tablen(msh_av),
								 msh_av, (*shell)->env);
		}
		free(msh_av);
	}
	return ;
}
