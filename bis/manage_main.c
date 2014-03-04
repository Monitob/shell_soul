#include <mnsh.h>

void	check_env(void)
{
	if (!environ || !(*environ))
	{
		ft_putstr_fd("[\x1b[31mDOSESHELL Environment error\x1b[0m] -->", 2);
		ft_putstr_fd("\x1b[33m No environment found !\x1b[0m\n", 2);
		exit(1);
	}
}

void	clear_screen(char **av)
{
	if (fork() == 0)
	{
		execve("/usr/bin/clear", av, environ);
	}
	else
		wait(NULL);
}

void	handle_signal(int signo)
{
	(void)signo;
	write(0, "\b\b", 2);
	write(0, "  ", 2);
	write(0, "\b\b", 2);
	write(0, "\n", 1);
	ft_putstr("\x1b[35m[\x1b[32mDoseShell\x1b[35m]\x1b[0m ");
}

