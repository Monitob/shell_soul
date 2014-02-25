/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tercs_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernabe <jbernabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/25 02:51:39 by jbernabe          #+#    #+#             */
/*   Updated: 2014/02/25 04:06:44 by jbernabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	tercs_edit_line(t_command *key)
{
	if (key->buffer[0] == 27 && key->buffer[1] == 91
			&& key->buffer[2] == 51)
	{
		TPUTS(nd);
		key->curr_hist->cursor++;
	}
	if (key->buffer[2] == 68 && key->curr_hist->cursor > 0)
	{
		TPUTS(le);
		key->curr_hist->cursor--;
	}
}

void	tercs_up_hist(t_command *key)
{
	if (key->buffer[0] == 27 && key->buffer[1] == 91 && key->buffer[2] == 65
			&& key->curr_hist)
		ft_putstr("do the history");

}

void	tercs_down_hist(t_command *key)
{
	if (key->buffer[0] == 27 && key->buffer[1] == 91 && key->buffer[2] == 66
			&& key->curr_hist)
		ft_putstr("down");
}

void	tercs_insert(t_command *key)
{
	int	i;

	if (key->buffer[0] >= 32 && key->buffer[0] <= 126)
	{
		i = key->curr_hist->line_len;
		while (i != key->curr_hist->cursor)
		{
			key->buffer[i] = key->buffer[i - 1];
			i++;
		}
		/*il faut decider si le buffer pour la line sera en dur
		 * o dynamic*/
//		key->line[key->cursor] = *key->buffer;
		key->curr_hist->cursor++;
		key->curr_hist->line_len++;
		ft_putstr(key->buffer);
}

void	tercs_delete_hist(t_command *key)
{
	ft_putstr("delete");
}

void	exec_line(t_command *key)
{
	ft_putstr("execute");
}

