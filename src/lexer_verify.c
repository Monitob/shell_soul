/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_verify.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernabe <jbernabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/03 19:51:16 by jbernabe          #+#    #+#             */
/*   Updated: 2014/03/26 19:02:11 by jbernabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		cursor_control2(t_letter *list_let)
{
	int		i;

	i = 0;
	tputs(tgetstr("bt", NULL), 1, trcs_putchar);
	while (i < ft_list_len(list_let))
	{
		tputs(tgetstr("le", NULL), 1, trcs_putchar);
		i++;
	}
	tputs(tgetstr("bt", NULL), 1, trcs_putchar);
}

void		cursor_control(t_letter *list_let)
{
	int		i;

	i = 0;
	tputs(tgetstr("bt", NULL), 1, trcs_putchar);
	tputs(tgetstr("do", NULL), 1, trcs_putchar);
	while (i < ft_list_len(list_let))
	{
		tputs(tgetstr("le", NULL), 1, trcs_putchar);
		i++;
	}
	tputs(tgetstr("bt", NULL), 1, trcs_putchar);
}

void			ft_start_lexer(t_shell **shell, t_letter **list_let)
{
	t_history	*hist;

	hist = NULL;
	if (!shell || !list_let)
		return ;
	if (list_let)
	{
		init_history(*list_let, &hist);
		char_to_string(&(*shell)->data, *list_let);
		tputs(tgetstr("bt", NULL), 1, trcs_putchar);
		cursor_control(*list_let);
		if (tcsetattr((*shell)->tcs->tty_fd, TCSADRAIN,
					&((*shell)->tcs->term_save)) == -1)
			exit(0);
		lex_verify(shell, list_let);
		if (tcsetattr((*shell)->tcs->tty_fd, TCSADRAIN, &((*shell)->tcs->term_fd)) == -1)
			exit(0);
		cursor_control2(*list_let);
		show_prompt(shell);
		ft_delete_list(list_let);
		init_line(*shell);
		free((*shell)->data->line);
	}
}

void		lex_verify(t_shell **shell, t_letter **let)
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
				(*shell)->env = buil(ft_tablen(msh_av), msh_av, (*shell)->env);
		}
	}
	return ;
}
