/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 18:58:35 by srabah-m          #+#    #+#             */
/*   Updated: 2014/03/27 19:23:57 by srabah-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doseshell.h"

int	new_env_pwd(t_shell *shell, char *path)
{
	t_env	*tmp;

	tmp = shell->env->next;
	while (tmp != shell->env)
	{
		if ((ft_strncmp(tmp->var, "PWD=", 4)) == 0)
		{
			tmp->var = ft_strcat("PWD=", path);
			if (tmp->var == NULL)
				return (-1);
			return (1);
		}
		tmp = tmp->next;
	}
	return (1);
}

int	cd_home(t_shell	*shell)
{
	if (shell->home == NULL)
		return (0);
	if (chdir(shell->home) == -1)
		ft_putstr_fd("cd: Could not access home directory.\n", 2);
	else
	{
		shell->old_pwd = shell->pwd;
		shell->pwd = shell->home;
		return (new_env_pwd(shell, shell->home));
	}
	return (0);
}

int	cd_path(t_cmd *cmd, t_shell *shell)
{
	char	*path;

	path = globing_for_cd(cmd);
	if (path == NULL)
		return (0);
	if (chdir(path) == -1)
		ft_putstr_fd("cd: Could not access directory.\n", 2);
	else
	{
		if (path[0] != '/')
		{
			if ((path = ft_strcat("/", path)) == NULL
				|| (path = ft_strcat(shell->pwd, path)) == NULL)
				return (-1);
		}
		shell->old_pwd = shell->pwd;
		shell->pwd = path;
		return (new_env_pwd(shell, path));
	}
	return (0);
}

int	dash_cd(t_shell *shell)
{
	if (shell->old_pwd && chdir(shell->old_pwd) != -1)
	{
		swap_char(&shell->old_pwd, &shell->pwd);
		return (new_env_pwd(shell, shell->pwd));
	}
	else
		ft_putstr_fd("cd: Could not access previous directory.\n", 2);
	return (0);
}

int	my_cd(t_cmd *cmd, t_shell *shell)
{
	int	i;

	i = get_nb_arg(cmd);
	cmd = cmd->next;
	shell->home = get_home(shell->env);
	if (i == 1)
		return (cd_home(shell));
	if (i > 2)
		ft_putstr_fd("cd: Too many arguments.\n", 2);
	else if (ft_strncmp(cmd->next->word, "-", 1) == 0)
		return (dash_cd(shell));
	else
		return (cd_path(cmd, shell));
	return (0);
}
