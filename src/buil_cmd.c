/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buil_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flime <flime@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/16 12:30:57 by flime             #+#    #+#             */
/*   Updated: 2014/03/16 12:31:00 by flime            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

void	buil_cmd(const char *path, char **msh_av, char **env)
{
	pid_t			cmd;
	int				status;

	cmd = fork();
	if (cmd == 0)
	{
		execve(path, msh_av, env);
		exit(-1);
	}
	wait(&status);
}
