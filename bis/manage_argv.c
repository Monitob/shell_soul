#include <mnsh.h>

void	get_my_argv(void)
{
	int	i;
	i = 0;

	while (i < g_nb_cmds)
	{
		g_cmd[i].my_argv = ft_split_arg(g_cmd[i].cmd_name);
		i++;
	}
}
