/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 20:12:25 by srabah-m          #+#    #+#             */
/*   Updated: 2014/03/27 20:49:52 by srabah-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doseshell.h"

int	replace_cmd(t_cmd *tmp, t_env *tmp_his, t_env *his, t_cmd *replace)
{
	tmp->prev->next = replace->next;
	tmp->next->prev = replace->prev;
	replace->next->prev = tmp->prev;
	replace->prev->next = tmp->next;
	tmp = replace->next;
	free(replace);
	if ((his->prev->var = ft_strdup(tmp_his->var)) == NULL)
		return (-1);
	return (0);
}

int	replace_tild(t_cmd *tmp, t_env *env, char *home)
{
	char	*tmp_home;

	if ((tmp_home = get_home(env)))
	{
		if ((tmp_home = ft_strdup(tmp_home)) == NULL)
			return (ft_error("Error: Couldn't strdup\n"));
	}
	else if (home)
		tmp_home = home;
	else
		return (0);
	if (tmp->word[1] == '/')
		tmp->word = tmp->word + 1;
	else
		tmp->word[0] = '/';
	if ((tmp->word = ft_strcat(tmp_home, tmp->word)) == NULL)
		return (ft_error("Error: Couldn't strcat\n"));
	return (0);
}

int	replace_var(t_cmd *cmd, t_shell *shell)
{
	int		ret;
	t_cmd	*tmp;

	tmp = cmd->next;
	while (tmp != cmd)
	{
		if (tmp->word[0] == '!')
			if ((ret = replace_history(tmp, shell->his)) == -1 || ret == -2)
				return (ret);
		if (tmp->word[0] == '~')
			if (replace_tild(tmp, shell->env, shell->home) == -1)
				return (-1);
		tmp = tmp->next;
	}
	return (0);
}
