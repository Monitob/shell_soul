/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 19:19:15 by srabah-m          #+#    #+#             */
/*   Updated: 2014/03/27 21:18:23 by srabah-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doseshell.h"

t_env	*already_exist_var(t_cmd *tmp, t_env *var)
{
	int		i;
	t_env	*tmp_var;

	i = 0;
	while (tmp->word[i] && tmp->word[i] != '=')
		++i;
	tmp_var = var->next;
	while (tmp_var != var)
	{
		if (ft_strncmp(tmp->word, tmp_var->var, i) == 0)
			return (tmp_var);
		tmp_var = tmp_var->next;
	}
	return (NULL);
}

void	remove_var_builtin(t_env *exist)
{
	free(exist->content);
	free(exist->var);
	exist->prev->next = exist->next;
	exist->next->prev = exist->prev;
	free(exist);
}

int		my_unset(t_cmd *cmd, t_shell *shell)
{
	t_cmd	*tmp;
	t_env	*exist;

	tmp = cmd->next->next;
	while (tmp != cmd)
	{
		if ((exist = already_exist_var(tmp, shell->var)))
			remove_var_builtin(exist);
		tmp = tmp->next;
	}
	return (1);
}
