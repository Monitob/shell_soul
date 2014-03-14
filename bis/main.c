/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/24 16:33:16 by srabah-m          #+#    #+#             */
/*   Updated: 2014/01/24 19:24:33 by srabah-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <mnsh.h>

char		**g_paths;
char		**g_full_paths;
t_cmd		g_cmd[256];
int			g_nb_cmds;

void	launch_cmds(void)
{
	int		i;
	t_env	e;

	i = 0;
	while (i < g_nb_cmds)
	{
		launch_cmds_set(i, &e);
		if (e.pid[i] == 0)
		{
			launch_set_fd(i, &e);
			launch_cmd(i);
		}
		else
		{
			close_fd(i, &e);
			i++;
		}
	}
	i = 0;
	while (i < g_nb_cmds)
	{
		waitpid(e.pid[i], NULL, 0);
		i++;
	}
}

void	mnsh_2(void)
{
	char	**strs;
	char	*str;

	ft_putstr(A_MAGENTA"[\x1b[32mDoseShell\x1b[35m]\x1b[0m ");
	while(get_next_line(0, &str) > 0)
	{
		str = trim_trailing_whitespaces(str);
		strs = ft_strsplit(str, ';');
		if (strs)
		{
			while (*strs)
			{
				get_cmds(*strs);
				init_cmds();
				get_redirs();
				get_my_argv();
				if (is_builtin_out())
					launch_builtin_out();
				else
					launch_cmds();
				strs++;
			}
		}
		ft_putstr("\x1b[35m[\x1b[32mDoseShell\x1b[35m]\x1b[0m ");
	}
}

int		main(int ac, char **av)
{
	(void)ac;

	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
	check_env();
	get_paths();
	clear_screen(av);
	mnsh_2();
	return (0);
}

