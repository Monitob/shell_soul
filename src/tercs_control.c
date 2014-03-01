/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tercs_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernabe <jbernabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/25 02:51:39 by jbernabe          #+#    #+#             */
/*   Updated: 2014/03/01 17:56:02 by jbernabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

#include <stdio.h> //

void	tercs_ascii(t_command *c_line, t_letter *let)
{
	(void)let;
	(void)c_line;
		return ;
}
void	tercs_up(t_command *c_line, t_letter *let)
{
	(void)let;
	(void)c_line;
		return ;
}

void	tercs_down(t_command *c_line, t_letter *let)
{
	(void)let;
	(void)c_line;
}

void	tercs_right(t_command *c_line, t_letter *let)
{
	if (let->next != NULL)
	{
		TGOTO(nd, 0, let->cursor++);
	}
	(void)c_line;
}

void	tercs_left(t_command *c_line, t_letter *let)
{
	if (let->next != NULL && let->cursor > 11)
	{
		TGOTO(le, 0, let->cursor--);
	}
	(void)c_line;
}
