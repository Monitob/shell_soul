/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_call.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/24 16:21:20 by srabah-m          #+#    #+#             */
/*   Updated: 2014/01/24 19:26:39 by srabah-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mnsh.h>

void	call_execve(int id)
{
	int	ret;
	int	i;

	i = 0;
	ret = -1;
	if (is_builtin(g_cmd[id].my_argv[0]))
		launch_builtin(g_cmd[id].my_argv[0]);
	else
	{
		attach_path(id);
		while ((g_full_paths[i])	&& ret == -1)
		{
			ret = execve(g_full_paths[i], g_cmd[id].my_argv, environ);
			i++;
		}
		if (ret == -1)
		{
			ft_putstr_fd("[\x1b[31m", 2);
			ft_putstr_fd(g_cmd[id].my_argv[0], 2);
			ft_putstr_fd("\x1b[0m] --> \x1b[33mCommand not found\x1b[0m\n", 2);
			exit(1);
		}
	}
}
