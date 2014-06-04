/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 19:10:45 by srabah-m          #+#    #+#             */
/*   Updated: 2014/03/27 19:12:09 by srabah-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doseshell.h"

void	aff_var(t_env *var)
{
	t_env	*tmp;

	tmp = var->next;
	while (tmp != var)
	{
		ft_putstr(tmp->var);
		ft_putchar('\t');
		ft_putstr(tmp->content);
		ft_putchar('\n');
		tmp = tmp->next;
	}
}

int		update_var(t_cmd *tmp, t_env *exist)
{
	int	i;

	i = 0;
	while (tmp->word[i] && tmp->word[i] != '=')
		++i;
	if (tmp->word[i])
		++i;
	free(exist->content);
	exist->content = ft_strdup(tmp->word + i);
	if (exist->content == NULL)
		return (-1);
	return (0);
}

int		create_var(t_cmd *tmp, t_env *var)
{
	int	i;

	i = 0;
	while (tmp->word[i] && tmp->word[i] != '=')
		++i;
	if (tmp->word[i])
	{
		tmp->word[i] = '\0';
		++i;
	}
	if (put_in_list(var, tmp->word) == NULL
		|| (var->prev->content = ft_strdup(tmp->word + i)) == NULL)
		return (-1);
	return (0);
}

int		my_set(t_cmd *cmd, t_shell *shell)
{
	t_cmd	*tmp;
	t_env	*exist;

	tmp = cmd->next->next;
	while (tmp != cmd)
	{
		if (verif_var(tmp))
		{
			if ((exist = already_exist_var(tmp, shell->var))
				&& update_var(tmp, exist) == -1)
				return (-1);
			else if (!exist)
				if (create_var(tmp, shell->var) == -1)
					return (-1);
		}
		else
		{
			ft_putstr_fd("Var should begin with a letter\n", 2);
			return (0);
		}
		tmp = tmp->next;
	}
	if (cmd->next->next == cmd)
		aff_var(shell->var);
	return (1);
}
