/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 19:19:54 by srabah-m          #+#    #+#             */
/*   Updated: 2014/03/27 21:17:56 by srabah-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doseshell.h"

int		remove_var(char *var_name, t_env *env)
{
	t_env		*tmp;
	char		*tmp_var;

	tmp_var = var_name;
	tmp = env->next;
	var_name = ft_strcat(var_name, "=");
	if (var_name == NULL)
		return (-1);
	while (tmp != env)
	{
		if (ft_strncmp(var_name, tmp->var, ft_strlen(var_name)) == 0)
		{
			tmp->prev->next = tmp->next;
			tmp->next->prev = tmp->prev;
			free(tmp->var);
			free(tmp);
			free(var_name);
			return (1);
		}
		tmp = tmp->next;
	}
	ft_putstr("error : ");
	ft_putstr(tmp_var);
	ft_putstr(" is not a var.\n");
	return (0);
}

int		option_star(t_shell *shell)
{
	t_env		*elem;
	char		*str_cpy;
	int			i;

	elem = shell->env->next;
	while (elem != shell->env)
	{
		i = 0;
		while (elem->var[i] && elem->var[i] != '=')
			++i;
		if ((str_cpy = ft_strndup(elem->var, i)) == NULL)
			return (-1);
		elem = elem->next;
		if (remove_var(str_cpy, shell->env) == -1)
			return (-1);
		free(str_cpy);
	}
	return (0);
}

int		my_unsetenv(t_cmd *cmd, t_shell *shell)
{
	t_cmd		*root;

	root = cmd;
	cmd = cmd->next->next;
	if (cmd == root)
	{
		ft_putstr("unsetenv: Too few arguments\n");
		return (9);
	}
	if (ft_strcmp(cmd->word, "*") == 0)
	{
		if ((option_star(shell)) == -1)
			return (-1);
	}
	else
	{
		while (cmd != root)
		{
			if (remove_var(cmd->word, shell->env) == -1)
				return (-1);
			cmd = cmd->next;
		}
	}
	return (1);
}
