/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 19:35:55 by srabah-m          #+#    #+#             */
/*   Updated: 2014/03/27 19:56:39 by srabah-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doseshell.h"

int	g_last_exit;

int		exit_raw_mode(void)
{
	struct termios	s_term;

	if (tcgetattr(0, &s_term) == -1)
		return (ft_error("Fail Tcgetattr()"));
	s_term.c_lflag = (ICANON | ECHO | ECHOCTL | ISIG);
	if (tcsetattr(0, 0, &s_term) == -1)
		return (ft_error("Fail tcsetattr()"));
	return (0);
}

int		raw_mode(void)
{
	struct termios	s_term;

	if (tcgetattr(0, &s_term) == -1)
		return (ft_error("Fail tcgetattr()"));
	s_term.c_lflag &= ~ICANON;
	s_term.c_lflag &= ~ECHO;
	s_term.c_cc[VMIN] = 1;
	s_term.c_cc[VTIME] = 0;
	if (tcsetattr(0, 0, &s_term) == -1)
		return (ft_error("Fail tcsetattr()"));
	return (0);
}

t_env	*add_to_history(t_shell *shell, char *cmd)
{
	return (put_in_list(shell->his, cmd));
}

void	reset_pos(t_shell *shell)
{
	t_env	*tmp;

	tmp = shell->his->next;
	while (tmp != shell->his)
	{
		tmp->pos = -1;
		tmp = tmp->next;
	}
	shell->his->pos = 1;
}

char	*get_cmd_input(t_shell *shell, int tty)
{
	char	*cmd;

	g_is_a_term = tty;
	g_last_exit = 1;
	if (dup2(shell->store_io[0], 0) == -1
		|| dup2(shell->store_io[1], 1) == -1)
		return (ft_error_null("Fail dup2"));
	display_prompt();
	if (tty)
	{
		if (raw_mode() == -1
			|| (cmd = termcaps_prompt(shell)) == NULL)
			return (NULL);
		reset_pos(shell);
		ft_putchar('\n');
	}
	else
		cmd = get_next_line(0);
	if (cmd == NULL
		|| add_to_history(shell, cmd) == NULL)
		return (NULL);
	return (cmd);
}
