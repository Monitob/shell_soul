/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tercs_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernabe <jbernabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/25 02:51:39 by jbernabe          #+#    #+#             */
/*   Updated: 2014/03/27 12:13:38 by jbernabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termios.h>
#include <term.h>
#include "shell.h"

void	tercs_ascii(t_command **c_line, t_letter **let)
{
	(void)let;
	(void)c_line;
	return ;
}

void	tercs_up(t_command **c_line, t_letter **let)
{
	(void)c_line;
	(void)let;
	return ;
}

void	tercs_down(t_command **c_line, t_letter **let)
{
	(void)let;
	(void)c_line;
}

void	tercs_right(t_command **c_line, t_letter **let)
{
	if (!(*let))
	{
		(void)let;
		(void)c_line;
		return ;
	}
	if (let && c_line)
	{
		if ((*let)->next == NULL)
			return ;
		if ((*let)->next)
		{
			tputs(tgetstr("nd", NULL), 1, trcs_putchar);
			(*let) = (*let)->next;
			(void)c_line;
		}
	}
}

void	tercs_left(t_command **c_line, t_letter **let)
{
	if (!(*let))
	{
		(void)let;
		(void)c_line;
		return ;
	}
	if ((*let)->letter != '\0')
	{
		if ((*let)->prev == NULL)
			return ;
		if (let)
		{
			tputs(tgetstr("le", NULL), 1, trcs_putchar);
			(*let) = (*let)->prev;
			(void)c_line;
			(void)let;
		}
	}
}
