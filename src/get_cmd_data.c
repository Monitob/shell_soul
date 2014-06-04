/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 19:27:39 by srabah-m          #+#    #+#             */
/*   Updated: 2014/03/27 19:34:55 by srabah-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doseshell.h"

t_cmd	*add_to_list(t_cmd *cmd_data, char *word)
{
	t_cmd	*new_elem;

	new_elem = (t_cmd *)malloc(sizeof(t_cmd));
	if (new_elem == NULL)
		return ((t_cmd *)ft_error_null("Fail malloc"));
	new_elem->word = word;
	new_elem->type = 0;
	new_elem->next = cmd_data;
	new_elem->prev = cmd_data->prev;
	cmd_data->prev->next = new_elem;
	cmd_data->prev = new_elem;
	return (new_elem);
}

int		space_tab_droid(char *str, int i)
{
	str[i] = '\0';
	i++;
	while (str[i] == ' ' || str[i] == '\t')
		++i;
	return (i);
}

int		double_quotes_droid(char *str, t_cmd *cmd, int i)
{
	str[i] = '\0';
	++i;
	add_to_list(cmd, str + i);
	while (str[i] != '\0' && str[i] != '"')
		++i;
	if (str[i] == '\0')
		return (i);
	str[i] = '\0';
	++i;
	return (i);
}

int		rest_droid(char *str, t_cmd *cmd, int i)
{
	add_to_list(cmd, str + i);
	while (str[i] != '\0'
		&& str[i] != ' '
		&& str[i] != '"'
		&& str[i] != '\t'
		&& str[i] != '\'')
		++i;
	return (i);
}

int		quote_droid(char *str, t_cmd *cmd, int i)
{
	str[i] = '\0';
	++i;
	add_to_list(cmd, str + i);
	while (str[i] != '\0' && str[i] != '\'')
		++i;
	if (str[i] == '\0')
		return (i);
	str[i] = '\0';
	++i;
	return (i);
}
