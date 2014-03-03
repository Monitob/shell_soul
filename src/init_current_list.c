/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_current_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernabe <jbernabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/27 12:14:31 by jbernabe          #+#    #+#             */
/*   Updated: 2014/03/02 19:14:59 by jbernabe         ###   ########.fr       */
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
	char_to_string(&(*sh)->data, *head, (*sh)->pro->prompt);
	ft_putchar(key);
//	ft_putstr((*sh)->data->line);
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

void			char_to_string(t_command **string, t_letter *head, char *prom)
{
	t_letter	*temp;
	int			len_tab;
	int			i;

	temp = head;
	len_tab = ft_list_len(temp);
	i = 0;
	(void)prom;
	(*string)->line = (char *)malloc(sizeof(char) * len_tab);
	while (temp != NULL)
	{
		(*string)->line[i] = temp->letter;
		temp = temp->next;
		i++;
	}
	(*string)->line[i] = '\0';
}
