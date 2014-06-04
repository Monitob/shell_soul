/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 19:45:22 by srabah-m          #+#    #+#             */
/*   Updated: 2014/03/27 19:49:37 by srabah-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doseshell.h"

void	display_formatted(t_env *tmp, char **cmd, int *i)
{
	int	j;

	j = 0;
	ft_putstr_fd(tgetstr("cb", NULL), 1);
	ft_putstr_fd(tgetstr("ce", NULL), 1);
	ft_putstr_fd(tgoto(tgetstr("ch", NULL), 1, 0), 1);
	display_prompt();
	if (tmp->var)
		while (tmp->var[j])
		{
			(*cmd)[j] = tmp->var[j];
			j++;
		}
	while (j < g_prompt.size)
		(*cmd)[j++] = '\0';
	ft_putstr_fd(*cmd, 1);
	*i = ft_strlen(*cmd) + 1;
}

void	history_prompt(char buf[3], int *i, char **cmd, t_shell *shell)
{
	t_env	*tmp;

	tmp = shell->his;
	while (tmp->pos == -1)
		tmp = tmp->next;
	tmp->pos *= -1;
	if (buf[2] == UP)
		tmp = tmp->prev;
	else if (buf[2] == DOWN)
		tmp = tmp->next;
	tmp->pos *= -1;
	display_formatted(tmp, cmd, i);
}
