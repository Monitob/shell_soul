/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_verify.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernabe <jbernabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/03 19:51:16 by jbernabe          #+#    #+#             */
/*   Updated: 2014/03/04 20:13:18 by jbernabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_start_lexer(t_shell **shell, t_letter **list_let)
{
	t_history	*hist;
	hist = NULL;
	int i;

	i = 0;

	char_to_string(&(*shell)->data, *list_let);
	TPUTS(do);
	while (i < (*shell)->pro->size_prompt)
	{
		TPUTS(le);
		i++;
	}
	i = 0;
	show_prompt(shell);
	while (i < (*shell)->pro->size_prompt)
	{
		TPUTS(nd);
		i++;
	}
	lex_verify(shell, list_let);
}

void	lex_verify(t_shell **shell, t_letter **let)
{
	(void)shell;
	(void)let;
	return ;
}
