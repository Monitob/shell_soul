#include <mnsh.h>

int		is_builtin_out(void)
{
	if (ft_strcmp(g_cmd[0].my_argv[0], "cd") == 0)
		return (1);
	else if (ft_strcmp(g_cmd[0].my_argv[0], "exit") == 0)
		return (1);
	else if (ft_strcmp(g_cmd[0].my_argv[0], "setenv") == 0)
		return (1);
	else if (ft_strcmp(g_cmd[0].my_argv[0], "unsetenv") == 0)
		return (1);
	else
		return (0);
}

void	launch_builtin_out(void)
{
	if (ft_strcmp(g_cmd[0].my_argv[0], "cd") == 0)
		change_dir();
	else if (ft_strcmp(g_cmd[0].my_argv[0], "exit") == 0)
		exit(0);
	else if (ft_strcmp(g_cmd[0].my_argv[0], "setenv") == 0)
		set_env();
	else if (ft_strcmp(g_cmd[0].my_argv[0], "unsetenv") == 0)
		unset_env();
}
