#include <mnsh.h>

void	add_tee_cmd(int i)
{
	int		j;
	char	new_cmd[256];
	int		nb;

	nb = g_cmd[i].nb_out;
	nb--;
	while (nb >= 0)
	{
		ft_strcpy(new_cmd, "tee ");
		j = g_nb_cmds + 1;
		while (j - 1 != i)
		{
			g_cmd[j] = g_cmd[j - 1];
			j--;
		}
		ft_strcat(new_cmd,  g_cmd[i].out_red[nb]);
		ft_strcpy(g_cmd[i + 1].cmd_name, new_cmd);
		g_cmd[i + 1].my_argv = ft_strsplit(new_cmd, ' ');
		g_cmd[i + 1].nb_out = 0;
		g_cmd[i + 1].nb_app = 0;
		g_cmd[i + 1].nb_inp = 0;
		++g_nb_cmds;
		nb--;
	}
}

void	launch_cmds_set(int i, t_env *e)
{
	if (i + 1 < g_nb_cmds)
	{
		if (pipe(e->new_fd) < 0)
			ft_fatal("pipe error");
	}
	if ((i + 1 < g_nb_cmds) && (g_cmd[i].nb_out > 0))
		add_tee_cmd(i);
	if (((e->pid)[i] = fork()) < 0)
		ft_fatal("fork error");
}

void	launch_cmd(int i)
{

	if ((i + 1 >= g_nb_cmds) && (g_cmd[i].nb_inp > 0))
		launch_red_inp(i);
	else if ((i + 1 >= g_nb_cmds) && (g_cmd[i].nb_out > 0))
		launch_red_end(i);
	else
		call_execve(i);
	exit(0);
}
