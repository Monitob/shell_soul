/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 19:12:14 by srabah-m          #+#    #+#             */
/*   Updated: 2014/03/27 19:24:08 by srabah-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doseshell.h"

t_env	*find_var(t_env *env, char *var)
{
	t_env		*root;

	root = env;
	env = env->next;
	while (root != env)
	{
		if (ft_strncmp(var, env->var, ft_strlen(var)) == 0)
			return (env);
		env = env->next;
	}
	return (root);
}

int		add_to_env(t_cmd *cmd, t_env *env)
{
	t_env		*var_env;
	t_cmd		*root;
	char		*var_name;
	char		*var_full;

	root = cmd;
	root->word = "";
	cmd = cmd->next->next;
	if ((var_name = ft_strcat(cmd->word, "=")) == NULL
		|| (var_env = find_var(env, var_name)) == NULL
		|| (var_full = ft_strcat(var_name, cmd->next->word)) == NULL)
		return (-1);
	free(var_name);
	if (var_env == env)
		put_in_list(env, var_full);
	else
	{
		free(var_env->var);
		var_env->var = var_full;
	}
	return (1);
}

int		add_to_env_glob(t_cmd *cmd, t_env *env)
{
	t_env		*var_env;
	t_cmd		*root;
	char		*var_name;
	char		*var_full;
	char		*var_glob;

	root = cmd;
	root->word = "";
	cmd = cmd->next->next;
	if ((var_name = ft_strcat(cmd->word, "=")) == NULL
		|| (var_env = find_var(env, var_name)) == NULL
		|| (var_glob = globing_for_setenv(cmd)) == NULL
		|| (var_full = ft_strcat(var_name, var_glob)) == NULL)
		return (-1);
	free(var_name);
	if (var_env == env)
		put_in_list(env, var_full);
	else
	{
		free(var_env->var);
		var_env->var = var_full;
	}
	return (1);
}

int		my_setenv(t_cmd *cmd, t_shell *shell)
{
	int		i;

	i = get_nb_arg(cmd);
	if (i > 3)
	{
		ft_putstr_fd("Error ! setenv : too many argument.\n", 1);
		return (0);
	}
	if (i == 1)
		return (my_env(cmd, shell));
	else if (i == 3 && is_there_a_star(cmd->next->next->next->word))
		return (add_to_env_glob(cmd, shell->env));
	return (add_to_env(cmd, shell->env));
}
