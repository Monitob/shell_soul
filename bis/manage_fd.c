#include <mnsh.h>

void	close_fd(int i, t_env *e)
{
	if (i >= 1)
	{
		close(e->old_fd[0]);
		close(e->old_fd[1]);
	}
	if (i + 1 < g_nb_cmds)
	{
		e->old_fd[0] = e->new_fd[0];
		e->old_fd[1] = e->new_fd[1];
	}
}

void	launch_set_fd(int i, t_env *e)
{
	if (i >= 1)
	{
		dup2(e->old_fd[0], 0);
		close(e->old_fd[0]);
		close(e->old_fd[1]);
	}
	if ((i + 1 < g_nb_cmds))
	{
		dup2(e->new_fd[1], 1);
		close(e->new_fd[0]);
		close(e->new_fd[1]);
	}
}
