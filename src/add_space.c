/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_space.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 18:17:20 by srabah-m          #+#    #+#             */
/*   Updated: 2014/03/27 21:42:05 by srabah-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doseshell.h"

t_token g_tokens[] =
{
	{REDI_D_LEFT, TYPE_D_LEFT},
	{REDI_D_RIGHT, TYPE_D_RIGHT},
	{REDI_RIGHT, TYPE_RIGHT},
	{REDI_LEFT, TYPE_LEFT},
	{AND, TYPE_AND},
	{BGROUND, TYPE_BGROUND},
	{OR, TYPE_OR},
	{CMD_SEP, TYPE_CMD_SEP},
	{PIPE, TYPE_PIPE},
	{NULL, TYPE_ARG}
};

int		nb_tokens(char *command)
{
	int	i;
	int	j;
	int	nb_tokens;

	i = 0;
	nb_tokens = 0;
	while (command[i])
	{
		j = 0;
		while (g_tokens[j].name
			&& ft_strncmp(command + i,
			g_tokens[j].name,
			ft_strlen(g_tokens[j].name)) != 0)
			j++;
		if (g_tokens[j].name)
		{
			i += ft_strlen(g_tokens[j].name);
			nb_tokens++;
		}
		else
			i++;
	}
	return (nb_tokens);
}

void	format_input(char *command, char *new_command)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (command[i])
	{
		k = 0;
		new_command[j++] = ' ';
		while (g_tokens[k].name
			&& ft_strncmp(command + i, g_tokens[k].name,
				ft_strlen(g_tokens[k].name)) != 0)
			k++;
		if (g_tokens[k].name && ft_strlen(g_tokens[k].name) > 1)
			new_command[j++] = command[i++];
		else if (!g_tokens[k].name)
			j--;
		new_command[j++] = command[i++];
		if (g_tokens[k].name)
			new_command[j++] = ' ';
	}
	new_command[j] = '\0';
}

char	*add_some_space(char *command)
{
	char	*new_command;

	new_command = malloc(ft_strlen(command) + 2 * nb_tokens(command) + 1);
	if (new_command == NULL)
		return (NULL);
	format_input(command, new_command);
	free(command);
	return (new_command);
}
