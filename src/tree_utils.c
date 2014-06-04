/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 20:22:58 by srabah-m          #+#    #+#             */
/*   Updated: 2014/03/27 20:43:23 by srabah-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doseshell.h"

int	g_tree_spec[] =
{
	TYPE_CMD_SEP,
	TYPE_OR,
	TYPE_AND,
	TYPE_PIPE,
	0
};

t_tree		*init_cmd_tree(int type)
{
	t_tree	*cmd_tree;
	t_param	*root_param;

	cmd_tree = malloc(sizeof(t_tree));
	root_param = malloc(sizeof(t_param));
	if (cmd_tree == NULL || root_param == NULL)
		return (NULL);
	cmd_tree->type = type;
	cmd_tree->param = root_param;
	root_param->next = root_param;
	root_param->prev = root_param;
	return (cmd_tree);
}

int			add_param(t_tree *tree, t_cmd *cmd)
{
	t_param	*new_param;

	new_param = malloc(sizeof(t_param));
	if (new_param == NULL)
		return (-1);
	new_param->cmd = cmd;
	new_param->tree = NULL;
	new_param->next = tree->param;
	new_param->prev = tree->param->prev;
	tree->param->prev->next = new_param;
	tree->param->prev = new_param;
	return (0);
}

int			new_tree(t_cmd **cmd, t_param *param, int *j)
{
	param->tree = init_cmd_tree(g_tree_spec[*j]);
	if (param->tree == NULL)
		return (-1);
	cut_cmd(param->tree, param->cmd, g_tree_spec[*j]);
	*cmd = param->cmd->prev;
	*j = 5;
	return (0);
}
