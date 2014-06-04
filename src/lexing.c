/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 18:28:41 by srabah-m          #+#    #+#             */
/*   Updated: 2014/03/27 21:11:36 by srabah-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doseshell.h"

t_token g_tok_lex[] =
{
	{REDI_D_LEFT, TYPE_D_LEFT},
	{REDI_D_RIGHT, TYPE_D_RIGHT},
	{REDI_RIGHT, TYPE_RIGHT},
	{REDI_LEFT, TYPE_LEFT},
	{AND, TYPE_AND},
	{OR, TYPE_OR},
	{CMD_SEP, TYPE_CMD_SEP},
	{PIPE, TYPE_PIPE},
	{NULL, TYPE_ARG}
};

void	lexing(t_cmd *cmd_data)
{
	int		i;
	t_cmd	*tmp_cmd;

	tmp_cmd = cmd_data->next;
	while (tmp_cmd != cmd_data)
	{
		i = 0;
		while (g_tok_lex[i].name
			&& ft_strncmp(tmp_cmd->word,
			g_tok_lex[i].name,
			ft_strlen(g_tok_lex[i].name)) != 0)
			i++;
		tmp_cmd->type = g_tok_lex[i].type;
		tmp_cmd = tmp_cmd->next;
	}
}
