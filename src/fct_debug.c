/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fct_debug.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernabe <jbernabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/02 12:30:39 by jbernabe          #+#    #+#             */
/*   Updated: 2014/03/27 12:12:34 by jbernabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
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

void			print_path(char **path)
{
	int	i;

	i = 0;
	while (path[i] != NULL)
	{
		ft_putstr(path[i]);
		write(1, "\n", 1);
		i++;
	}
}

void			display_list_test(t_letter *head)
{
	t_letter	*temp;

	temp = head;
	while (temp != NULL)
	{
		ft_putchar(temp->letter);
		temp = temp->prev;
	}
	write(1, "\n", 1);
}
