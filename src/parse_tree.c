/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 20:07:44 by srabah-m          #+#    #+#             */
/*   Updated: 2014/03/27 20:58:05 by srabah-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doseshell.h"

int	g_parse_tree[] =
{
	TYPE_CMD_SEP,
	TYPE_OR,
	TYPE_AND,
	TYPE_PIPE,
	0
};

void	clean_tree(t_tree *tree)
{
	t_param	*param;

	param = tree->param->next;
	while (param != tree->param)
	{
		if (param->tree)
		{
			clean_tree(param->tree);
			free(param->cmd);
			param->cmd = NULL;
		}
		param = param->next;
	}
}

int		check_tree_or_cmd(t_param *param, int i)
{
	int			j;
	t_param		*tmp_param;
	t_cmd		*tmp_cmd;

	tmp_param = param->next;
	while (tmp_param != param)
	{
		j = i;
		while (g_parse_tree[j])
		{
			tmp_cmd = tmp_param->cmd->next;
			while (tmp_cmd != tmp_param->cmd)
			{
				if (tmp_cmd->type == g_parse_tree[j])
					if (new_tree(&tmp_cmd, tmp_param, &j) == -1)
						return (-1);
				tmp_cmd = tmp_cmd->next;
			}
			j++;
		}
		tmp_param = tmp_param->next;
	}
	return (0);
}

int		clean_cmd(t_param *param, t_cmd *cmd, int i)
{
	t_param		*tmp;
	t_cmd		*tmp_cmd;
	t_cmd		*tmp_clean_cmd;

	tmp = param->next;
	while (tmp != param)
	{
		tmp_clean_cmd = init_cmd_data();
		tmp_cmd = tmp->cmd;
		while (tmp_cmd != cmd && tmp_cmd->type != g_parse_tree[i])
		{
			if (add_to_list(tmp_clean_cmd, tmp_cmd->word) == NULL)
				return (-1);
			tmp_clean_cmd->prev->type = tmp_cmd->type;
			tmp_cmd = tmp_cmd->next;
		}
		tmp->cmd = tmp_clean_cmd;
		tmp = tmp->next;
	}
	return (0);
}

int		cut_cmd(t_tree *tree, t_cmd *cmd, int type)
{
	int		i;
	t_cmd	*tmp_1;
	t_cmd	*tmp_2;

	i = 0;
	tmp_1 = cmd->next;
	while (tmp_1 != cmd)
	{
		tmp_2 = tmp_1;
		while (tmp_2 != cmd && tmp_2->type != type)
			tmp_2 = tmp_2->next;
		if (add_param(tree, tmp_1) == -1)
			return (-1);
		tmp_1 = (tmp_2 == cmd ? tmp_2 : tmp_2->next);
	}
	while (g_parse_tree[i] != type)
		i++;
	if (clean_cmd(tree->param, cmd, i) == -1
		|| check_tree_or_cmd(tree->param, i) == -1)
		return (-1);
	return (0);
}

t_tree	*get_tree(t_cmd *cmd_data)
{
	t_tree	*cmd_tree;

	if ((cmd_tree = init_cmd_tree(TYPE_CMD_SEP)) == NULL
		|| cut_cmd(cmd_tree, cmd_data, TYPE_CMD_SEP) == -1)
		return (NULL);
	clean_tree(cmd_tree);
	return (cmd_tree);
}
