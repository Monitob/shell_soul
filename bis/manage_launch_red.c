#include <mnsh.h>

static void	set_red_end(int nb_out, int i);
static void	set_inp(int i, int j, int *fd_inp);

void		launch_red_end(int i)
{
	int		nb_out;
	pid_t	pid_bis;

	nb_out = g_cmd[i].nb_out;
	while (nb_out > 0)
	{
		if ((pid_bis = fork()) == 0)
		{
			set_red_end(nb_out, i);
			call_execve(i);
			exit(0);
		}
		else
		{
			waitpid(pid_bis, NULL, 0);
			nb_out--;
		}
	}
}

static void	set_red_end(int nb_out, int i)
{
	int		fd_red;
	char	*name;

	name = g_cmd[i].out_red[nb_out - 1];
	if (g_cmd[i].is_app[nb_out - 1])
		fd_red = open(name, O_RDWR | O_CREAT | O_APPEND, 0777);
	else
		fd_red = open(name, O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fd_red < 0)
		ft_fatal("\x1b[31mError\x1b[0m while opening for red");
	if (dup2(fd_red, 1) < 0)
		ft_fatal("\x1b[31mError\x1[0m while copying fd's");
	close(fd_red);
}

void		launch_red_inp(int i)
{
	int		nb_inp;
	pid_t	pid_ter;
	int		j;
	int		fd_inp;

	nb_inp = g_cmd[i].nb_inp;
	j = 0;
	while (j < nb_inp)
	{
		if ((pid_ter = fork()) == 0)
		{
			set_inp(i, j, &fd_inp);
			exit(0);
		}
		else
		{
			waitpid(pid_ter, NULL, 0);
			close(fd_inp);
			j++;
		}
	}
}

static void	set_inp(int i, int j, int *fd_inp)
{
	*fd_inp = 0;
	if ((*fd_inp = open(g_cmd[i].inp_red[j], O_RDONLY)) < 0)
		ft_fatal("\x1b[31mError\x1b[0m  while opening");
	if (dup2(*fd_inp, 0) < 0)
		ft_fatal("\x1b[31mError\x1b[0m  while copying fd's");
	if (close(*fd_inp) < 0)
		ft_fatal("\x1b[31mError\x1b[0m  while closing one fd");
	if (g_cmd[i].nb_out > 0)
		launch_red_end(i);
	else
		call_execve(i);
}
