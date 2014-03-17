/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_fct_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernabe <jbernabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/16 20:07:35 by jbernabe          #+#    #+#             */
/*   Updated: 2014/03/16 20:10:43 by jbernabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void			ft_delete_list(t_letter **list_let)
{
	t_letter	*temp;

	temp = (*list_let)->prev;
	while (temp != NULL)
	{
		(*list_let)->letter = 0;
		*list_let = NULL;
		*list_let = temp;
		temp = temp->prev;
	}
}

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
