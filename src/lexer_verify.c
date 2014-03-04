/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_verify.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernabe <jbernabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/03 19:51:16 by jbernabe          #+#    #+#             */
/*   Updated: 2014/03/04 19:43:18 by jbernabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_start_lexer(t_shell **shell, t_letter **list_let)
{
	t_history	*hist;
	hist = NULL;

	char_to_string(&(*shell)->data, *list_let);
	TGOTO(bt,0, (*shell)->pro->size_prompt);
	show_prompt(shell);
	lex_verify(shell, list_let);
}

void	lex_verify(t_shell **shell, t_letter **let)
{
	(void)shell;
	(void)let;
	return ;
}
