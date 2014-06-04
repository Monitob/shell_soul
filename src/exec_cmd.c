/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 18:50:45 by srabah-m          #+#    #+#             */
/*   Updated: 2014/03/27 21:41:47 by srabah-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doseshell.h"

t_builtin	g_built[] =
{
	{"history", my_history},
	{"set", my_set},
	{"unset", my_unset},
	{"setenv", my_setenv},
	{"unsetenv", my_unsetenv},
	{"env", my_env},
	{"echo", my_echo},
	{"exit", my_exit},
	{"cd", my_cd},
	{"alias", my_alias},
	{"unalias", my_unalias},
	{NULL, NULL}
};

int		exe_alias(t_alias *alias, t_cmd *cmd, t_shell *shell)
{
	char		*cmd_full;
	t_cmd		*root;

	root = cmd;
	cmd = cmd->next->next;
	if ((cmd_full = ft_strdup(alias->cmd)) == NULL)
		return (-1);
	while (cmd != root)
	{
		if ((cmd_full = ft_strcat_redi(cmd_full, " ")) == NULL
			|| (cmd_full = ft_strcat_redi(cmd_full, cmd->word)) == NULL)
			return (-1);
		cmd = cmd->next;
	}
	return (parsexec(cmd_full, shell));
}

int		check_alias(t_cmd *cmd, t_shell *shell)
{
	t_alias	*alias;

	alias = shell->alias;
	while (alias != NULL)
	{
		if (ft_strcmp(alias->name, cmd->next->word) == 0)
			return (exe_alias(alias, cmd, shell));
		alias = alias->next;
	}
	return (2);
}

int		check_builtin(t_cmd *cmd, t_shell *shell)
{
	int	i;

	i = 0;
	while (g_built[i].name != NULL)
	{
		if (ft_strcmp(g_built[i].name, cmd->next->word) == 0)
		{
			g_last_exit = g_built[i].fct_builtin(cmd, shell);
			return (g_last_exit);
		}
		i++;
	}
	return (2);
}

int		exe_cmd(t_cmd *cmd, t_shell *shell)
{
	int			ret;
	t_cmd		*tmp;

	if (cmd->next == cmd)
		return (0);
	if ((ret = check_alias(cmd, shell)) != 2)
		return (ret);
	if ((ret = back_ground(cmd, shell)) == -1)
		return (-1);
	else if (ret == 0)
	{
		if ((ret = check_builtin(cmd, shell)) != 2)
			return (ret);
		tmp = cmd->next->next;
		while (tmp != cmd)
			tmp = globing(tmp);
		return (my_exec(cmd, shell));
	}
	return (1);
}
