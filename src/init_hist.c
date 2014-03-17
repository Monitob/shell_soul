/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernabe <jbernabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/01 19:46:41 by jbernabe          #+#    #+#             */
/*   Updated: 2014/03/15 18:25:45 by jbernabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
/*
static t_history	*creat_head_history(t_letter *current_list)
{
	t_history	*start;

	if (!(start = (t_history *)malloc(sizeof(t_history))))
		return (NULL);
	start->curr = current_list;
	start->next_h = NULL;
	start->prev_h = NULL;
	return (start);
}*/

static void			ft_hist_to_list(t_history **l_hist, t_history **new_el)
{
	t_history	*temp;

	temp = *l_hist;
	while (temp->next_h != NULL)
		temp = temp->next_h;
	temp->next_h = *new_el;
	(*new_el)->prev_h = temp;
	*l_hist = *new_el;
}

void				ft_print_hist(t_history *hist_p)
{
	t_history	*temp;

	temp = hist_p;
	while (temp != NULL)
	{
		display_list_test(temp->curr);
		temp = temp->next_h;
		write(1, "\n", 1);
	}
}

void				init_history(t_letter *current_list, t_history **l_hist)
{
	t_history	*new_line;

	if (!(new_line = (t_history *)malloc(sizeof(t_history))))
		return ;
	new_line->curr = current_list;
	new_line->next_h = NULL;
	new_line->prev_h = NULL;
	//ft_putstr("after head hist_p::->   \n");
	if (*l_hist == NULL)
	{
		*l_hist = new_line;
	//	ft_putendl("		creat_head::->  \n");
	}
	else
	{
	//	ft_putendl("		after head::->   \n");
		ft_hist_to_list(l_hist, &new_line);
	}
	//ft_print_hist(*l_hist); //
}
