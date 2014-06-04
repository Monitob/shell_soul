/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 19:00:12 by srabah-m          #+#    #+#             */
/*   Updated: 2014/03/27 21:25:00 by srabah-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doseshell.h"

void	check_option(t_cmd *tmp)
{
	int	i;

	i = 0;
	while (tmp->word[i])
	{
		if (tmp->word[i] == '*')
		{
			globing_for_echo(tmp);
			return ;
		}
		else
			++i;
	}
	ft_putstr(tmp->word);
}

int		my_echo(t_cmd *cmd, t_shell *shell)
{
	t_cmd	*tmp;
	int		option;

	(void)shell;
	tmp = cmd->next->next;
	option = 1;
	while (tmp != cmd)
	{
		if (tmp == cmd->next->next && ft_strcmp(tmp->word, "-n") == 0)
		{
			option = 0;
			tmp = tmp->next;
		}
		if (tmp != cmd)
		{
			check_option(tmp);
			if (tmp->next != cmd && ft_strcmp(tmp->word, "-n") == 1)
				ft_putchar(' ');
			tmp = tmp->next;
		}
	}
	if (option)
		ft_putchar('\n');
	return (1);
}
