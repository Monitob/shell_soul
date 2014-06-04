/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_data_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 19:28:43 by srabah-m          #+#    #+#             */
/*   Updated: 2014/03/27 21:16:32 by srabah-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doseshell.h"

t_cmd	*str_to_linked_list(char *str, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t')
			i = space_tab_droid(str, i);
		else if (str[i] == '"')
			i = double_quotes_droid(str, cmd, i);
		else if (str[i] == '\'')
			i = quote_droid(str, cmd, i);
		else if (str[i] != ' '
			&& str[i] != '\t'
			&& str[i] != '"'
			&& str[i] != '\'')
			i = rest_droid(str, cmd, i);
	}
	return (cmd);
}

t_cmd	*init_cmd_data(void)
{
	t_cmd	*cmd_data;

	cmd_data = malloc(sizeof(t_cmd));
	if (cmd_data == NULL)
		return ((t_cmd *)ft_error_null("Fail malloc"));
	cmd_data->next = cmd_data;
	cmd_data->prev = cmd_data;
	return (cmd_data);
}

t_cmd	*get_cmd_data(char *command)
{
	t_cmd	*cmd_data;

	if ((cmd_data = init_cmd_data()) == NULL
		|| str_to_linked_list(command, cmd_data) == NULL)
		return (NULL);
	return (cmd_data);
}
