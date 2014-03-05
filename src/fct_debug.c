/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fct_debug.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernabe <jbernabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/02 12:30:39 by jbernabe          #+#    #+#             */
/*   Updated: 2014/03/05 19:52:57 by jbernabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_letter		*creat_new_element(char let)
{
	t_letter	*root;

	if (!(root = (t_letter *)malloc(sizeof(t_letter))))
		return (NULL);
	root->letter = let;
	root->next = NULL;
	root->prev = NULL;
	return (root);
}

void			ft_char_to_list(t_letter **ele, t_letter *new_el)
{
	t_letter	*temp;

	temp = *ele;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new_el;
	new_el->prev = temp;
	*ele = new_el;
}

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
		temp = temp->next;
	}
	write(1, "\n", 1);
}
