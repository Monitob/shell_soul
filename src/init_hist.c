/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernabe <jbernabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/01 19:46:41 by jbernabe          #+#    #+#             */
/*   Updated: 2014/03/03 20:06:45 by jbernabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static t_history	*creat_head_history(t_letter *current_list)
{
	t_history	*start;

	if (!(start = (t_history *)malloc(sizeof(t_history))))
		return (NULL);
	start->curr = current_list;
	start->next_h = NULL;
	start->prev_h = NULL;
	return (start);
}

static void		ft_hist_to_list(t_history **l_hist, t_history *new_el)
{
	t_history	*temp;

	temp = *l_hist;
	while (temp->next_h != NULL)
		temp = temp->next_h;
	temp->next_h = new_el;
	new_el->prev_h = temp;
	*l_hist = new_el;
}
	
void	init_history(t_letter *current_list, t_history **l_hist)
{
	t_history	*new_line;

	if (!(new_line = (t_history *)malloc(sizeof(t_history))))
		return ;
	new_line->curr = current_list;
	new_line->next_h = NULL;
	new_line->prev_h = NULL;
	if (*l_hist == NULL)
	{
		*l_hist = creat_head_history(current_list);
	}
	else
	{
		ft_hist_to_list(l_hist, new_line);
	}
}
