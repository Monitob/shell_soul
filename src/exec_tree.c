/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 18:52:27 by srabah-m          #+#    #+#             */
/*   Updated: 2014/03/27 21:31:53 by srabah-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doseshell.h"

int	(*g_manage_streams[4])(char *, t_shell *) =
{
	redi_right,
	redi_d_right,
	redi_left,
	redi_d_left
};

t_exec	g_tree_pos[3] =
{
	{TYPE_AND, and_exec},
	{TYPE_OR, or_exec},
	{TYPE_PIPE, pipe_exec}
};

void	remove_redi(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd->next;
	while (tmp != cmd)
	{
		if (tmp->type == TYPE_LEFT
			|| tmp->type == TYPE_RIGHT
			|| tmp->type == TYPE_D_LEFT
			|| tmp->type == TYPE_D_RIGHT)
		{
			tmp = tmp->next->next;
			del_node(tmp->prev);
			del_node(tmp->prev);
		}
		else
			tmp = tmp->next;
	}
}

int		find_redi_and_exec(t_cmd *cmd, t_shell *shell)
{
	int		ret;
	t_cmd	*tmp;

	tmp = cmd->next;
	while (tmp != cmd)
	{
		while (tmp != cmd
			&& tmp->type != TYPE_LEFT
			&& tmp->type != TYPE_D_LEFT
			&& tmp->type != TYPE_RIGHT
			&& tmp->type != TYPE_D_RIGHT)
			tmp = tmp->next;
		if (tmp != cmd)
		{
			if ((ret = g_manage_streams[tmp->type - 2](tmp->next->word, shell))
				== -1
				|| ret == -2)
				return (ret);
			tmp = tmp->next->next;
		}
	}
	remove_redi(cmd);
	return (exe_cmd(cmd, shell));
}

int		should_i_exec_other_cmd(t_tree *tree, t_param *param, t_shell *shell)
{
	int	i;

	i = 0;
	if ((param == tree->param->next && tree->type != TYPE_PIPE)
		|| tree->type == TYPE_CMD_SEP)
		return (1);
	while (g_tree_pos[i].type != tree->type)
		i++;
	return (g_tree_pos[i].fct(tree, param, shell));
}

int		exec_tree(t_tree *tree, t_shell *shell)
{
	int		ret;
	t_param	*param;

	shell->pipe = 0;
	param = tree->param->next;
	while (param != tree->param)
	{
		if (dup2(shell->store_io[0], 0) == -1
			|| dup2(shell->store_io[1], 1) == -1)
			return (ft_error("Couldn't dup2\n"));
		if ((ret = should_i_exec_other_cmd(tree, param, shell)) == -1
			|| ret == 0)
			return (ret);
		if (param->tree && exec_tree(param->tree, shell) == -1)
			return (-1);
		else if (!param->tree)
			if (find_redi_and_exec(param->cmd, shell) == -1)
				return (-1);
		if (tree->type == TYPE_PIPE)
			pipe_exit(tree, param);
		param = param->next;
	}
	return (0);
}
