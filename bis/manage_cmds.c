#include <mnsh.h>

static void	loop_cmds(char *str);

void		init_cmds(void)
{
	int	i;

	i = 0;
	while (i < g_nb_cmds)
	{
		g_cmd[i].nb_out = 0;
		g_cmd[i].nb_app = 0;
		g_cmd[i].nb_inp = 0;
		g_cmd[i].fd_in = 0;
		g_cmd[i].fd_out = 1;
		i++;
	}
}


void		get_cmds(char *str)
{
	if (!str)
	{
		g_nb_cmds = 0;
		return ;
	}
	while (is_space(*str))
		str++;
	loop_cmds(str);
}

static void	loop_cmds(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (*str)
	{
		if (*str == '|')
		{
			while (is_space(g_cmd[i].cmd_name[j - 1]))
				j--;
			g_cmd[i].cmd_name[j] = '\0';
			j = 0;
			i++;
			while (is_space(*str) || *str == '|')
				str++;
		}
		g_cmd[i].cmd_name[j++] = *str;
		str++;
	}
	while (is_space(g_cmd[i].cmd_name[j - 1]))
		j--;
	g_cmd[i].cmd_name[j] = '\0';
	g_nb_cmds = i + 1;
}
