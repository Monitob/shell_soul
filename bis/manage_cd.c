#include <mnsh.h>

static char	*cd_home(void);
static void	cd_error(char *file);

void		change_dir(void)
{
	char	cwd[256];
	char	*full_cwd;

	if ((!g_cmd[0].my_argv[1]) || (ft_strcmp(g_cmd[0].my_argv[1], "~") == 0))
		full_cwd = cd_home();
	else if (g_cmd[0].my_argv[1][0] == '/')
	{
		if ((full_cwd = (char *)malloc(sizeof(char) * 256)) == NULL)
			ft_fatal("[\x1b[31mcd\x1b[0m] --> Couldn't malloc");
		ft_strcpy(full_cwd, g_cmd[0].my_argv[1]);
	}
	else
	{
		getcwd(cwd, (size_t)256);
		full_cwd = ft_strjoin(cwd, "/");
		full_cwd = ft_strjoin(full_cwd, g_cmd[0].my_argv[1]);
	}
	if ((chdir(full_cwd)) == -1)
		cd_error(g_cmd[0].my_argv[1]);
}

static char	*cd_home(void)
{
	int		i;

	i = 0;
	while (environ[i])
	{
		if (ft_strncmp(environ[i], "HOME=", 5) == 0)
			break;
		i++;
	}
	return (ft_strdup(environ[i] + 5));
}



static void	cd_error(char *file)
{
	ft_putstr_fd("[\x1b[31mcd\x1b[0m] -> no such file or directory: ", 2);
	ft_putstr("\x1b[33m");
	ft_putendl(file);
	ft_putstr("\x1b[0m");
}
