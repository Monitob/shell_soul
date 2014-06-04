/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rep_history_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 20:16:05 by srabah-m          #+#    #+#             */
/*   Updated: 2014/03/27 20:50:10 by srabah-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doseshell.h"

int	name_f(t_cmd *tmp, t_env *his)
{
	char	*cpy;
	t_cmd	*replace;
	t_env	*tmp_his;

	tmp_his = his->prev->prev;
	while (tmp_his != his)
	{
		if (strstr(tmp_his->var, tmp->word + 1))
		{
			if ((cpy = ft_strdup(tmp_his->var)) == NULL
				|| (replace = get_cmd_data(cpy)) == NULL)
				return (-1);
			return (replace_cmd(tmp, tmp_his, his, replace));
		}
		tmp_his = tmp_his->prev;
	}
	ft_putstr("Error, last event not found\n");
	return (-2);
}

int	last_event(t_cmd *tmp, t_env *his)
{
	t_cmd	*replace;
	char	*cpy;

	if (his->prev->prev == his)
	{
		ft_putstr("Error, last event not found\n");
		return (-2);
	}
	if ((cpy = ft_strdup(his->prev->prev->var)) == NULL
		|| (replace = get_cmd_data(cpy)) == NULL)
		return (-1);
	return (replace_cmd(tmp, his->prev->prev, his, replace));
}

int	replace_history(t_cmd *tmp, t_env *his)
{
	if (tmp->word[1] >= '0' && tmp->word[1] <= '9')
		return (num_f(tmp, his));
	else if (tmp->word[1] == '-' &&
		tmp->word[2] >= '0' && tmp->word[2] <= '9')
		return (revnum_f(tmp, his));
	else if (tmp->word[1] == '!')
		return (last_event(tmp, his));
	else
		return (name_f(tmp, his));
	return (0);
}
