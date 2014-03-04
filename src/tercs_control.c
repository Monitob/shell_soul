/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tercs_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernabe <jbernabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/25 02:51:39 by jbernabe          #+#    #+#             */
/*   Updated: 2014/03/04 16:16:51 by jbernabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

#include <stdio.h> //

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
	if (let)
	{
		if ((*let)->next == NULL)
			return ;
		if ((*let)->next)
		{	
			TPUTS(nd);
			(*let) = (*let)->next;
			(void)c_line;
		}
	}
}

void	tercs_left(t_command **c_line, t_letter **let)
{

	if (let)
	{
		if ((*let)->prev == NULL)
				return ;
		if (let)
		{
			TPUTS(le);
			(*let) = (*let)->prev;
			(void)c_line;
			(void)let;
		}
	}
}
