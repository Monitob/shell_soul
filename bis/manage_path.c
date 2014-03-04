#include <mnsh.h>

void	get_paths(void)
{
	int	i;
	int	nb_paths;

	i = 0;
	while (1)
	{
		if (ft_strncmp(environ[i], "PATH=", 5) == 0)
			break;
		else
			i++;
	}
	g_paths = ft_strsplit(environ[i] + 5, ':');
	nb_paths = 0;
	while (g_paths[nb_paths])
	{
		g_paths[nb_paths] = ft_strjoin(g_paths[nb_paths], "/");
		nb_paths++;
	}
	if (!(g_full_paths = (char **)malloc(sizeof(char *) * (nb_paths + 1))))
		ft_fatal("\x1b[31mMalloc error\x1b[0m");
}

void	attach_path(int id)
{
	int	i;

	i = 0;
	while (g_paths[i])
	{
		g_full_paths[i] = ft_strjoin(g_paths[i], g_cmd[id].my_argv[0]);
		i++;
	}
	g_full_paths[i] = NULL;
}
