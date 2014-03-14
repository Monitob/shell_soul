/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_current_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernabe <jbernabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/03 19:30:09 by jbernabe          #+#    #+#             */
/*   Updated: 2014/03/14 18:22:29 by jbernabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <stdio.h> //


static void		insert_char(t_letter **current_list, char key, t_prompt *pro)
{
	t_letter	*let;

	let = NULL;
	if (!(let = (t_letter *)malloc(sizeof(t_letter))))
		return ;
	let->letter = key;
	let->next = NULL;
	let->prev = NULL;
	if(*current_list == NULL)
	{
		if((*current_list = creat_new_element('*')) == NULL)
			return ;
		ft_char_to_list(current_list, let);
		(void)pro;
		pro->cursor_l = 1;
	}
	else
	{
		ft_char_to_list(current_list, let);
		pro->cursor_l++;
	}
}

void			init_ascii(t_letter **head, char key, t_shell **sh)
{
	insert_char(head, key, (*sh)->pro);
	if (key == 13)
		return ;
	trcs_putchar(key);
}

int		ft_list_len(t_letter *head)
{
	t_letter	*temp;
	int			i;

	temp = head;
	i = 0;
	while (temp != NULL)
	{
		temp = temp->prev;
		i++;
	}
	return (i);
}

static void			recur_display(t_letter *let, t_command **string, int i)
{
	if (let)
	{
		if (let->prev == NULL)
			return ;
		else
			recur_display(let->prev, string, i - 1);
		(*string)->line[i] = let->letter;
	}
}

void			char_to_string(t_command **string, t_letter *head)
{
	t_letter	*temp;
	int			len_tab;

	temp = head;
	len_tab = ft_list_len(temp) - 1;
	(*string)->line = (char *)malloc(sizeof(char) * len_tab + 1);
	recur_display(temp, string, len_tab - 1);
	(*string)->line[len_tab] = '\0'; 
}
