/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 18:41:46 by srabah-m          #+#    #+#             */
/*   Updated: 2014/03/27 21:35:41 by srabah-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doseshell.h"

int	check_nbr_cmd(int nb_cmd, int previous, t_cmd **tmp, t_cmd *cmd)
{
	if (!nb_cmd && !(*tmp != cmd && previous == TYPE_CMD_SEP))
		return (ft_error_parsing("Invalid command\n"));
	if (*tmp != cmd)
		previous = (*tmp)->type;
	if (*tmp != cmd)
	{
		*tmp = (*tmp)->next;
		if (*tmp == cmd && (*tmp)->prev->type != TYPE_CMD_SEP)
			return (ft_error_parsing("Invalid command\n"));
		else if (*tmp == cmd)
			return (previous);
	}
	return (previous);
}

int	check_null_cmd(t_cmd *cmd)
{
	int		nb_cmd;
	int		previous;
	t_cmd	*tmp;

	nb_cmd = 0;
	tmp = cmd->next;
	previous = TYPE_CMD_SEP;
	while (tmp != cmd)
	{
		nb_cmd = 0;
		while (tmp != cmd && tmp->type != TYPE_PIPE && tmp->type != TYPE_AND
			&& tmp->type != TYPE_OR && tmp->type != TYPE_CMD_SEP)
		{
			if (tmp->type == TYPE_CMD)
				nb_cmd++;
			tmp = tmp->next;
		}
		if (nb_cmd == 0 && tmp != cmd
			&& (tmp->type == TYPE_PIPE || tmp->type == TYPE_AND
			|| tmp->type == TYPE_OR))
			return (ft_error_parsing("Invalid null command"));
		if ((previous = check_nbr_cmd(nb_cmd, previous, &tmp, cmd)) == -1)
			return (-1);
	}
	return (1);
}

int	check_redi_pipe(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd->next;
	while (tmp != cmd)
	{
		while (tmp != cmd && tmp->type != TYPE_PIPE)
			tmp = tmp->next;
		if (tmp == cmd)
			return (0);
		while (tmp->prev != cmd
			&& tmp->prev->type != TYPE_CMD_SEP
			&& tmp->prev->type != TYPE_AND
			&& tmp->prev->type != TYPE_OR)
			tmp = tmp->prev;
		tmp = verif_redi_pipe(cmd, tmp);
		if (tmp == NULL)
			return (-1);
	}
	return (0);
}
