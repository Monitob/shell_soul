/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fct_debug.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernabe <jbernabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/02 12:30:39 by jbernabe          #+#    #+#             */
/*   Updated: 2014/03/02 12:36:15 by jbernabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void			ft_key_int_type(char key[8], int type)
{
	ft_putnbr(key[0]);
	ft_putnbr(key[1]);
	ft_putnbr(key[2]);
	ft_putnbr(key[3]);
	ft_putnbr(key[4]);
	ft_putchar('\n');
	ft_putnbr(type);  
}

void			display_list_test(t_letter *head)
{
	t_letter	*temp;
	int			i;

	temp = head;
	i = 0;
	i = ft_list_len(temp);
	ft_putnbr(i);
	while (temp != NULL)
	{
		ft_putchar(temp->letter);
		temp = temp->next;
	}
	write(1, "\n", 1);
}
