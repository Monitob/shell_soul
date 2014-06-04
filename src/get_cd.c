/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 19:27:10 by srabah-m          #+#    #+#             */
/*   Updated: 2014/03/27 19:27:34 by srabah-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doseshell.h"

char	*get_home(t_env *env)
{
	t_env	*tmp;

	tmp = env->next;
	while (tmp != env)
	{
		if (ft_strncmp(tmp->var, "HOME=", 5) == 0)
			return (tmp->var + 5);
		tmp = tmp->next;
	}
	return (NULL);
}

char	*get_cd_path(t_cmd *cmd, t_shell *shell)
{
	char	*path;

	(void)shell;
	cmd = cmd->next;
	path = cmd->word;
	return (path);
}

void	swap_char(char **old_pwd, char **pwd)
{
	char	*swap;

	swap = *old_pwd;
	*old_pwd = *pwd;
	*pwd = swap;
}
