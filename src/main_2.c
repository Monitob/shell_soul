/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 20:02:23 by srabah-m          #+#    #+#             */
/*   Updated: 2014/03/27 20:03:27 by srabah-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doseshell.h"

void	display_prompt(void)
{
	ft_putstr("\x1b[35m[\x1b[32mDoseShell\x1b[35m\x1b[35m]\x1b[0m%");
}

void	sig_manage(int sig)
{
	int		i;

	i = 0;
	if (g_is_a_term)
	{
		g_prompt.i = 1;
		while (i < g_prompt.size)
			g_prompt.cmd[i++] = '\0';
	}
	(void)sig;
	ft_putchar('\n');
}

void	clean_tree_mem(t_tree *tree)
{
	t_param	*tmp_param;
	t_cmd	*tmp_cmd;

	tmp_param = tree->param->next;
	while (tmp_param != tree->param)
	{
		if (tmp_param->tree)
			clean_tree_mem(tmp_param->tree);
		else
		{
			tmp_cmd = tmp_param->cmd->next;
			while (tmp_cmd != tmp_param->cmd)
			{
				tmp_cmd = tmp_cmd->next;
				free(tmp_cmd->prev);
			}
			free(tmp_cmd);
		}
		tmp_param = tmp_param->next;
		free(tmp_param->prev);
	}
	free(tmp_param);
	free(tree);
}

void	clean_command_mem(t_cmd *cmd_data, char *command)
{
	t_cmd	*tmp_cmd;

	tmp_cmd = cmd_data->next;
	while (tmp_cmd != cmd_data)
	{
		tmp_cmd = tmp_cmd->next;
		free(tmp_cmd->prev);
	}
	free(cmd_data);
	free(command);
}

void	clean_memory(t_tree *cmd_tree, t_cmd *cmd_data, char *cmd)
{
	clean_tree_mem(cmd_tree);
	clean_command_mem(cmd_data, cmd);
}
