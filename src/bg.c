/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bg.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 18:38:57 by srabah-m          #+#    #+#             */
/*   Updated: 2014/03/27 21:10:38 by srabah-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doseshell.h"

int	back_ground(t_cmd *cmd, t_shell *shell)
{
	t_cmd	*tmp;
	int		pid;

	tmp = cmd->next;
	while (tmp->next != cmd)
		tmp = tmp->next;
	if (ft_strncmp(tmp->word, "&", 1) == 0)
	{
		if ((pid = fork()) == -1)
			return (ft_error("Couldn't fork properly\n"));
		if (pid == 0)
		{
			setpgid(getpid(), getpid());
			del_node(cmd->prev);
			exe_cmd(cmd, shell);
			return (-1);
		}
		else
			return (1);
	}
	return (0);
}
