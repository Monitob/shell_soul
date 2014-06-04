/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 19:05:05 by srabah-m          #+#    #+#             */
/*   Updated: 2014/03/27 21:24:52 by srabah-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doseshell.h"

int	father_exec(int pid, t_shell *shell)
{
	int		status;
	char	*ret;

	if (shell->pipe == 0)
		waitpid(pid, &status, 0);
	if (shell->pipe == 0 && WIFEXITED(status) == 0)
	{
		ret = strsignal(WTERMSIG(status));
		if (ret == NULL)
			return (-1);
		ft_putstr(ret);
		ft_putchar('\n');
		g_last_exit = 0;
	}
	else
		g_last_exit = 1;
	return (0);
}

int	exec_path(char **cmd_tab, char **env_tab, t_shell *shell)
{
	int	pid;

	if (access(cmd_tab[0], X_OK) == -1)
	{
		ft_putstr("ERROR --> command not found :");
		ft_putstr(cmd_tab[0]);
		ft_putchar('\n');
		g_last_exit = 0;
		return (0);
	}
	if ((pid = fork()) == -1)
		return (ft_error("error : fork fail\n"));
	if (pid == 0)
	{
		execve(cmd_tab[0], cmd_tab, env_tab);
		return (-1);
	}
	else
		return (father_exec(pid, shell));
}

int	my_exec(t_cmd *cmd, t_shell *shell)
{
	char	**env_tab;
	char	**cmd_tab;
	char	*path;

	if ((env_tab = env_in_tab(shell->env)) == NULL)
		return (-1);
	if ((path = get_valid_path(cmd->next->word, shell, env_tab)) == NULL)
		return (-1);
	cmd->next->word = path;
	if ((cmd_tab = cmd_in_tab(cmd)) == NULL)
		return (-1);
	return (exec_path(cmd_tab, env_tab, shell));
}
