/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_current_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernabe <jbernabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/27 12:14:31 by jbernabe          #+#    #+#             */
/*   Updated: 2014/02/28 13:17:06 by jbernabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	insert_char(t_letter **current_list, char key)
{
	t_letter	*let;
	t_letter	*temp;

	temp = NULL;
	if (!(let = (t_letter *)malloc(sizeof(t_letter))))
		return ;
	let->letter = key;
	let->next = NULL;
	let->prev = NULL;
	if (*current_list == NULL)
		*current_list = let;
	else
	{
		temp = *current_list;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = let;
		let->prev = temp;
	}
}

void	init_ascii(t_letter **head, char key)
{
	insert_char(head, key);
	ft_putchar(key);
}

int		ft_list_len(t_letter *head)
{
	t_letter	*temp;
	int			i;

	temp = head;
	i = 0;
	while (temp != NULL)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}

void	char_to_string(t_command **string, t_letter *head)
{
	t_letter	*temp;
	int			len_tab;
	int			i;

	temp = head;
	len_tab = ft_list_len(temp);
	i = 0;
	(*string)->line = (char *)malloc(sizeof(char) * len_tab);
	while (temp != NULL)
	{
		(*string)->line[i] = temp->letter;
		temp = temp->next;
		i++;
	}
}


void	display_list_test(t_letter *head)
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
