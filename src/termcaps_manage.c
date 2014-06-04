/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps_manage.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 20:19:27 by srabah-m          #+#    #+#             */
/*   Updated: 2014/03/27 20:43:41 by srabah-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doseshell.h"

int	check_arrow(char buf[3], char **cmd, int *i, t_shell *shell)
{
	if (buf[2] == LEFT)
	{
		if (*i > 1)
		{
			ft_putstr_fd("\b", 1);
			*i -= 1;
		}
	}
	else if (buf[2] == RIGHT)
	{
		if ((int)(*i) <= (int)ft_strlen(*cmd))
		{
			ft_putstr_fd(tgetstr("nd", NULL), 1);
			*i += 1;
		}
	}
	else if (buf[2] == DOWN || buf[2] == UP)
		history_prompt(buf, i, cmd, shell);
	return (0);
}

int	ctrl_termcaps(char buf[3], char **cmd, int *i, t_shell *shell)
{
	(void)i;
	(void)shell;
	if (buf[0] == CTRLD)
	{
		ft_putchar('\n');
		return (-1);
	}
	else if (buf[0] == CTRLL)
	{
		ft_putstr_fd(tgetstr("cl", NULL), 1);
		display_prompt();
		ft_putstr_fd(*cmd, 1);
	}
	return (0);
}

int	add_char(char buf[3], char **cmd, int *i, t_shell *shell)
{
	(void)shell;
	(*cmd)[*i - 1] = buf[0];
	*i += 1;
	ft_putchar(buf[0]);
	return (0);
}

int	backspace_termcaps(char buf[3], char **cmd, int *i, t_shell *shell)
{
	(void)buf;
	(void)shell;
	if (*i > 1)
	{
		ft_putstr_fd("\b \b", 1);
		*i -= 1;
		(*cmd)[*i - 1] = (*cmd)[*i] ? ' ' : '\0';
	}
	return (0);
}
