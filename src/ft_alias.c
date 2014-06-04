/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alias.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 18:55:01 by srabah-m          #+#    #+#             */
/*   Updated: 2014/03/27 21:27:25 by srabah-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doseshell.h"

t_alias		*put_alias_in_list(t_alias *alias, char *name, char *cmd)
{
	t_alias	*ellem;

	if ((ellem = malloc(sizeof(*ellem))) == NULL
		|| (ellem->name = ft_strdup(name)) == NULL
		|| (ellem->cmd = ft_strdup(cmd)) == NULL)
		return (ft_error_null("fail malloc / strdup"));
	ellem->next = alias;
	return (ellem);
}

int			find_word(char *word, char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (ft_strncmp(word, str + i, ft_strlen(word)) == 0)
		{
			str += i + ft_strlen(word);
			if (*str == '\0' || *str == ' ')
				return (1);
		}
		i++;
	}
	return (0);
}

void		check_loop(t_alias *name, t_alias *cmd, t_alias **root)
{
	while (name != NULL)
	{
		cmd = *root;
		while (cmd != NULL)
		{
			if (find_word(name->name, cmd->cmd) == 1)
			{
				ft_putstr_fd("error : alias can loop\n", 2);
				put_alias_off_list(root, cmd);
			}
			cmd = cmd->next;
		}
		name = name->next;
	}
}

t_alias		*alias_loop(t_alias *tmp)
{
	ft_putstr(tmp->name);
	ft_putchar('\t');
	ft_putstr(tmp->cmd);
	ft_putstr("\n");
	return (tmp->next);
}

int			my_alias(t_cmd *cmd, t_shell *data)
{
	int		i;
	t_alias	*tmp;

	tmp = data->alias;
	i = get_nb_arg(cmd);
	if (i == 1)
	{
		while (tmp)
			tmp = alias_loop(tmp);
		return (1);
	}
	else if (i != 3)
	{
		ft_putstr_fd("error aliasing -> bad arg number\n", 2);
		return (0);
	}
	cmd = cmd->next;
	if ((data->alias = put_alias_in_list(data->alias, cmd->next->word,
		cmd->next->next->word)) == NULL)
		return (-1);
	check_loop(data->alias, data->alias, &data->alias);
	return (1);
}
