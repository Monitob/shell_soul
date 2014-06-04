/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 19:50:39 by srabah-m          #+#    #+#             */
/*   Updated: 2014/03/27 19:59:10 by srabah-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doseshell.h"

char		*get_pwd(char **env)
{
	int		i;

	i = 0;
	while (env[i] && ft_strncmp("PWD=", env[i], 4) != 0)
		i++;
	if (env[i] == NULL)
		return (NULL);
	else
		return (env[i] + 4);
}

char		*get_path_home(t_env *env)
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

t_shell		*init_shell(char **env, int *tty)
{
	t_shell	*shell;

	if ((shell = (t_shell *)malloc(sizeof(t_shell))) == NULL)
	{
		ft_putstr_fd("Error during malloc allocation\n", 2);
		g_main_return = -1;
		return (NULL);
	}
	if (*tty == 1)
	{
		if (init_term(env) < 0)
			*tty = 0;
	}
	if ((store_io(shell) == -1)
		|| (shell->env = get_env(env)) == NULL
		|| (shell->his = get_root()) == NULL
		|| (shell->var = get_root()) == NULL)
		return (NULL);
	shell->pwd = get_pwd(env);
	shell->path = get_path(env);
	shell->alias = NULL;
	shell->home = get_path_home(shell->env);
	shell->old_pwd = NULL;
	return (shell);
}
