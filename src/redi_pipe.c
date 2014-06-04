/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redi_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 20:50:40 by srabah-m          #+#    #+#             */
/*   Updated: 2014/03/27 20:54:38 by srabah-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doseshell.h"

void	init_redi(int redi[4])
{
	redi[0] = 0;
	redi[1] = 0;
	redi[2] = 0;
	redi[3] = 0;
}

void	stock_redi(int redi[4], t_cmd *tmp)
{
	if (tmp->type == TYPE_LEFT)
		redi[0] = 1;
	else if (tmp->type == TYPE_D_LEFT)
		redi[1] = 1;
	else if (tmp->type == TYPE_RIGHT)
		redi[2] = 1;
	else if (tmp->type == TYPE_D_RIGHT)
		redi[3] = 1;
}

int		check_and_verif_redi_pipe(int *start, int redi[4],
	t_cmd *tmp, t_cmd *cmd)
{
	if (*start)
	{
		*start = 0;
		if (redi[2] || redi[3])
			return (ft_error_parsing("Reformat the redirection\n"));
		else
			return (0);
	}
	else if (tmp != cmd && tmp->type == TYPE_PIPE
		&& (redi[0] || redi[1] || redi[2] || redi[3]))
		return (ft_error_parsing("Reformat the redirection\n"));
	else if (redi[0] || redi[1])
		return (ft_error_parsing("Reformat the redirection\n"));
	return (0);
}

t_cmd	*verif_redi_pipe(t_cmd *cmd, t_cmd *tmp)
{
	int	start;
	int	redi[4];

	start = 1;
	init_redi(redi);
	while (tmp != cmd && tmp->type != TYPE_CMD_SEP
		&& tmp->type != TYPE_AND && tmp->type != TYPE_OR)
	{
		while (tmp != cmd && tmp->type != TYPE_CMD_SEP
			&& tmp->type != TYPE_AND && tmp->type != TYPE_OR
			&& tmp->type != TYPE_PIPE)
		{
			stock_redi(redi, tmp);
			tmp = tmp->next;
		}
		if (check_and_verif_redi_pipe(&start, redi, tmp, cmd) == -1)
			return (NULL);
		if (tmp != cmd && tmp->type == TYPE_PIPE)
			tmp = tmp->next;
		init_redi(redi);
	}
	return (tmp);
}
