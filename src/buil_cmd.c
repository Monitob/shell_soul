/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buil_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernabe <jbernabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/16 12:30:57 by flime             #+#    #+#             */
/*   Updated: 2014/03/25 02:06:59 by jbernabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "shell.h"

#include <stdio.h>

void	buil_cmd(const char *path, char **msh_av, char **env)
{
	pid_t			cmd;
	int				status;

	if (!chdir(path))
	{
		ft_putstr("42sh: permission denied: ");
		ft_putendl(path);
	}
	cmd = fork();
	if (cmd == 0)
	{
		execve(path, msh_av, env);
		exit(-1);
	}
	wait(&status);
}
