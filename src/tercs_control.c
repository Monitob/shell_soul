/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tercs_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernabe <jbernabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/25 02:51:39 by jbernabe          #+#    #+#             */
/*   Updated: 2014/02/28 19:16:25 by jbernabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

#include <stdio.h> //

void	tercs_up(t_command *c_line, t_letter *let,  char key[8])
{
	printf("UP:: %s", c_line->line);
	printf("UP:: %zu", let->cursor);
	(void)key;
		return ;
}

void	tercs_down(t_command *c_line, t_letter *let,  char key[8])
{
	ft_putnbr(key[0]);
	ft_putchar(' ');
	ft_putnbr(key[1]);
	ft_putchar(' ');
	ft_putnbr(key[2]);
	ft_putchar(' ');
	ft_putnbr(key[3]);
	ft_putchar(' ');
	ft_putnbr(key[4]);
	ft_putchar(' ');
	printf("DONW:: %s", c_line->line);
	printf("DOWN:: %zu", let->cursor);
	(void)key;
}

void	tercs_right(t_command *c_line, t_letter *let,  char key[8])
{
		TPUTS(nd);
	printf("RIGHT:: %s", c_line->line);
	printf("RIGHT:: %zu", let->cursor);
	(void)key;
}

void	tercs_left(t_command *c_line, t_letter *let,  char key[8])
{
		TPUTS(le);
	printf("LEFT:: %s", c_line->line);
	printf("LEFT:: %zu", let->cursor);
	(void)key;
}
