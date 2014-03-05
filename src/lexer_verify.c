/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_verify.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernabe <jbernabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/03 19:51:16 by jbernabe          #+#    #+#             */
/*   Updated: 2014/03/05 19:31:01 by jbernabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <unistd.h>

void	ft_start_lexer(t_shell **shell, t_letter **list_let)
{
	t_history	*hist;
	int i;

	hist = NULL;
	i = 0;
	if (!shell || !list_let)
		return ;
	if (list_let)
	{
		char_to_string(&(*shell)->data, *list_let);
		TPUTS(bt);
		TPUTS(do);
		while (i <  ft_list_len(*list_let))
		{
			TPUTS(le);
			i++;
		}
		TPUTS(bt);
		show_prompt(shell);
	}
	lex_verify(shell, list_let);
}

void	lex_verify(t_shell **shell, t_letter **let)
{
	
	(void)shell;
	(void)let;
	return ;
}
