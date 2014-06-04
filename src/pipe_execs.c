/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_execs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 20:11:34 by srabah-m          #+#    #+#             */
/*   Updated: 2014/03/27 20:12:19 by srabah-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doseshell.h"

int	and_exec(t_tree *tree, t_param *param, t_shell *shell)
{
	(void)tree;
	(void)param;
	(void)shell;
	return (g_last_exit ? 1 : 0);
}

int	or_exec(t_tree *tree, t_param *param, t_shell *shell)
{
	(void)tree;
	(void)param;
	(void)shell;
	return (g_last_exit ? 0 : 1);
}

int	pipe_exec(t_tree *tree, t_param *param, t_shell *shell)
{
	static int	i = 0;
	static int	k = 1;
	static int	pipe_fd[2][2];

	if (param == tree->param->next)
	{
		if (i == 0)
			i++;
		else
		{
			if (k == -1)
				close(pipe_fd[0][0]);
			else if (pipe_fd[1][0] != -1)
				close(pipe_fd[1][0]);
		}
		pipe_fd[1][0] = -1;
		return (start_pipe(pipe_fd, &k, shell));
	}
	else if (param == tree->param->prev)
		return (end_pipe(pipe_fd, &k, shell));
	else
		return (mid_pipe(pipe_fd, &k, shell));
}
