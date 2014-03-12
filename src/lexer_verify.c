/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_verify.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernabe <jbernabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/03 19:51:16 by jbernabe          #+#    #+#             */
/*   Updated: 2014/03/11 19:31:51 by jbernabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <unistd.h>

void	cursor_control(t_letter *list_let)
{
	int i;

	i = 0;
	TPUTS(bt);
	TPUTS(do);
	while (i <  ft_list_len(list_let))
	{
		TPUTS(le);
		i++;
	}
	TPUTS(bt);
}

void	ft_delete_list(t_letter **list_let)
{
	t_letter *temp1;

	temp1 = *list_let;
	while (temp1->next != NULL)
	{
		temp1 = temp1->next;
	}
}

void	ft_start_lexer(t_shell **shell, t_letter **list_let)
{
	//	t_history	*hist;
	//	int i;

	//	hist = NULL;
	//	i = 0;
	if (!shell || !list_let)
		return ;
	if (list_let)
	{
		char_to_string(&(*shell)->data, *list_let);
		cursor_control(*list_let);
		TPUTS(bt);
		lex_verify(shell, list_let);
		TPUTS(cr);
		cursor_control(*list_let);
		show_prompt(shell);
	//	ft_delete_list(list_let);
	}
}

void	lex_verify(t_shell **shell, t_letter **let)
{
	char	**msh_av;

	if ((*shell)->data || (*let)->letter)
	{
		if ((msh_av = ft_strsplit((*shell)->data->line, ' ')) == 0)
			return ;
		if (msh_av[0] != NULL)
			ft_parser(msh_av, (*shell)->env);
	}
	return ;
}
