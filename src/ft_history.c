/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 19:08:24 by srabah-m          #+#    #+#             */
/*   Updated: 2014/03/27 21:24:42 by srabah-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doseshell.h"

void	aff_history(t_shell *shell)
{
	t_env	*tmp;

	tmp = shell->his->next;
	while (tmp != shell->his)
	{
		ft_putstr(tmp->var);
		ft_putchar('\n');
		tmp = tmp->next;
	}
}

void	history_dash_c(t_shell *shell)
{
	t_env	*tmp;

	tmp = shell->his->next;
	while (tmp != shell->his)
	{
		tmp = tmp->next;
		free(tmp->prev->var);
		free(tmp->prev);
	}
	tmp->pos = 1;
	tmp->next = tmp;
	tmp->prev = tmp;
}

int		my_history(t_cmd *cmd, t_shell *shell)
{
	if (cmd->next->next != cmd &&
		ft_strcmp(cmd->next->next->word, "-c") == 0)
		history_dash_c(shell);
	else
		aff_history(shell);
	return (1);
}
