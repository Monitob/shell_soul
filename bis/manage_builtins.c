#include <mnsh.h>

int		is_builtin(char *cmd)
{
		if (ft_strcmp(cmd, "pwd") == 0)
			return (1);
		else if (ft_strcmp(cmd, "env") == 0)
			return (1);
		else
			return (0);
}

void	launch_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "pwd") == 0)
		my_pwd();
	else if (ft_strcmp(cmd, "env") == 0)
		get_env();
}

void	my_pwd(void)
{
	char	cwd[256];

	if (getcwd(cwd, (size_t)256) == NULL)
		perror("\x1b[31mpwd\x1b[0m -> ");
	ft_putendl(cwd);
}

