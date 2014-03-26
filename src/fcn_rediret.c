/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fcn_rediret.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernabe <jbernabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/24 19:17:29 by jbernabe          #+#    #+#             */
/*   Updated: 2014/03/26 19:34:31 by jbernabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <stdio.h>

static void		ft_push_parser(t_parser *new_el, t_parser **el_parser)
{
	t_parser	*temp;

	if (*el_parser && new_el)
	{
		temp = *el_parser;
		while (temp->next != NULL)
		{
			dprintf(3, "ADD2 in while %p\n", temp->next);
			temp = temp->next;
		}
		temp->next = new_el;
	}
	else
	{
		dprintf(3, "add  null -> %p\n", el_parser);
		*el_parser = new_el;
	}
}

static int		ft_get_id(char *str)
{
	if (ft_strcmp(str, "|"))
		return (1);
	else if (ft_strcmp(str, ">"))
		return (2);
	else if (ft_strcmp(str, "<"))
		return (3);
	else if (ft_strcmp(str, ">>"))
		return (4);
	else if (ft_strcmp(str, ">>"))
		return (5);
	else if (ft_strcmp(str, "||"))
		return (6);
	else if (ft_strcmp(str, "&&"))
		return (7);
	else if (ft_strcmp(str, "&&"))
		return (8);
	else
		return (0);
}

void			ft_element_parser(char **av, t_parser **el_parser)
{
	int			i;
	t_parser	*new_el;

	i = 0;
	while (av[i] != NULL)
	{
		if (!(new_el = (t_parser *)malloc(sizeof(t_parser))))
			return ;
		new_el->cmd = av[i];
		dprintf(1, "cmd %s\n", new_el->cmd);
		new_el->id = ft_get_id(av[i]);
		new_el->next = NULL;
		if (el_parser == NULL)
		{
			dprintf(1, "el_parser NULL %p", *el_parser);
			*el_parser = new_el;
		}
		else
			ft_push_parser(new_el, el_parser);
		i++;
	}
}
