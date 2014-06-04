/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 19:21:58 by srabah-m          #+#    #+#             */
/*   Updated: 2014/03/27 19:24:53 by srabah-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doseshell.h"

int	get_nb_arg(t_cmd *cmd)
{
	t_cmd		*root;
	int			i;

	root = cmd;
	cmd = cmd->next;
	i = 0;
	while (cmd != root)
	{
		++i;
		cmd = cmd->next;
	}
	return (i);
}

int	is_there_a_star(char *word)
{
	int	i;

	i = 0;
	while (word[i])
	{
		if (word[i] == '*')
			return (1);
		++i;
	}
	return (0);
}

int	verif_var(t_cmd	*tmp)
{
	if ((tmp->word[0] >= 'a' && tmp->word[0] <= 'z')
		|| (tmp->word[0] >= 'A' && tmp->word[0] <= 'Z'))
		return (1);
	return (0);
}
