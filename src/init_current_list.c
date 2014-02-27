/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_current_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernabe <jbernabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/27 12:14:31 by jbernabe          #+#    #+#             */
/*   Updated: 2014/02/27 14:12:51 by jbernabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"


static t_letter *insert_char(t_letter **current_list, char key[8])
{
	t_letter	*let;
	t_letter	*temp;

	let = (t_letter *)malloc(sizeof(t_letter));
	let->letter = key[0];
	let->next = NULL;
	let->prev = NULL;
	if (*current_list == NULL)
		return (let);
	else
	{
		temp = *current_list;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next =  let;
		let->prev = temp;
		return (*current_list);
	}
}

t_letter	*init_ascii(char key[8])
{
	static t_letter	*current_list = NULL;

	current_list = insert_char(&current_list, key);
	ft_putchar(key[0]);
	return (current_list);
}
