/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 20:03:56 by srabah-m          #+#    #+#             */
/*   Updated: 2014/03/27 20:05:24 by srabah-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doseshell.h"

void	pipe_exit(t_tree *tree, t_param *param)
{
	static int	exit_value = 1;

	exit_value = exit_value ? g_last_exit : 0;
	if (param == tree->param->prev)
	{
		g_last_exit = exit_value;
		exit_value = 1;
	}
}

int		start_pipe(int pipe_fd[2][2], int *k, t_shell *shell)
{
	*k = 1;
	shell->pipe = 1;
	if (pipe(pipe_fd[0]) == -1
		|| dup2(pipe_fd[0][1], 1) == -1)
		return (ft_error("Error in dup2\n"));
	return (1);
}

int		end_pipe(int pipe_fd[2][2], int *k, t_shell *shell)
{
	shell->pipe = 0;
	if (*k == 1)
	{
		if (dup2(pipe_fd[0][0], 0) == -1)
			return (ft_error("Error in dup2\n"));
		close(pipe_fd[0][1]);
		if (pipe_fd[1][0] != -1)
			close(pipe_fd[1][0]);
	}
	else
	{
		if (dup2(pipe_fd[1][0], 0) == -1)
			return (ft_error("Error in dup2\n"));
		close(pipe_fd[1][1]);
		close(pipe_fd[0][0]);
	}
	*k *= -1;
	return (1);
}

int		mid_pipe(int pipe_fd[2][2], int *k, t_shell *shell)
{
	shell->pipe = 1;
	if (*k == 1)
	{
		if (pipe_fd[1][0] != -1)
			close(pipe_fd[1][0]);
		if (pipe(pipe_fd[1]) == -1
			|| dup2(pipe_fd[1][1], 1) == -1
			|| dup2(pipe_fd[0][0], 0) == -1)
			return (ft_error("Error in dup2\n"));
		close(pipe_fd[0][1]);
	}
	else
	{
		close(pipe_fd[0][0]);
		if (pipe(pipe_fd[0]) == -1
			|| dup2(pipe_fd[0][1], 1) == -1
			|| dup2(pipe_fd[1][0], 0) == -1)
			return (ft_error("Error in dup2\n"));
		close(pipe_fd[1][1]);
	}
	*k *= -1;
	return (1);
}
