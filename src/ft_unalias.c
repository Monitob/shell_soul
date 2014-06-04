/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unalias.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 19:18:24 by srabah-m          #+#    #+#             */
/*   Updated: 2014/03/27 21:18:45 by srabah-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doseshell.h"

void	put_alias_off_list(t_alias **alias, t_alias *focus)
{
	t_alias	*tmp;

	if (*alias == focus)
	{
		*alias = alias[0]->next;
		return ;
	}
	tmp = *alias;
	while (tmp->next != focus)
		tmp = tmp->next;
	tmp->next = focus->next;
}

int		my_unalias(t_cmd *cmd, t_shell *shell)
{
	t_cmd		*tmp;
	t_alias		*tmp_alias;

	tmp = cmd->next->next;
	if (tmp == cmd)
	{
		ft_putstr_fd("No parameters to unalias.\n", 2);
		return (0);
	}
	while (tmp != cmd)
	{
		tmp_alias = shell->alias;
		while (tmp_alias)
		{
			if (ft_strcmp(tmp->word, tmp_alias->name) == 0)
				put_alias_off_list(&shell->alias, tmp_alias);
			tmp_alias = tmp_alias->next;
		}
		tmp = tmp->next;
	}
	return (1);
}
