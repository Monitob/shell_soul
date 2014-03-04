#include <mnsh.h>
static void	redir_out(int nb_out, int id, int *i);
static void	redir_inp(int nb_inp, int id, int *i);

int			store_redirs(int id, int i)
{
	if (g_cmd[id].cmd_name[i] == '>')
		redir_out(g_cmd[id].nb_out, id, &i);
	else if (g_cmd[id].cmd_name[i] == '<')
		redir_inp(g_cmd[id].nb_inp, id, &i);
	return (i);
}

static void	redir_inp(int nb_inp, int id, int *i)
{
	int	j;

	j = 0;
	(*i)++;
	while (is_space(g_cmd[id].cmd_name[*i]))
		(*i)++;
	while (g_cmd[id].cmd_name[*i] != '\0' && !is_sep(g_cmd[id].cmd_name[*i]))
		g_cmd[id].inp_red[nb_inp][j++] = g_cmd[id].cmd_name[(*i)++];
	while (is_space(g_cmd[id].inp_red[nb_inp][j - 1]))
		j--;
	g_cmd[id].inp_red[nb_inp][j] = '\0';
	g_cmd[id].nb_inp++;
}

static void	redir_out(int nb_out, int id, int *i)
{
	int	j;

	j = 0;
	(*i)++;
	if (g_cmd[id].cmd_name[*i] == '>')
	{
		g_cmd[id].is_app[nb_out] = 1;
		(*i)++;
	}
	else
		g_cmd[id].is_app[nb_out] = 0;
	while (is_space(g_cmd[id].cmd_name[*i]))
		(*i)++;
	while (g_cmd[id].cmd_name[*i] != '\0' && !is_sep(g_cmd[id].cmd_name[*i]))
		g_cmd[id].out_red[nb_out][j++] = g_cmd[id].cmd_name[(*i)++];
	while (is_space(g_cmd[id].out_red[nb_out][j - 1]))
		j--;
	g_cmd[id].out_red[nb_out][j] = '\0';
	g_cmd[id].nb_out++;
}

void	set_redirs(int id)
{
	int	i;

	i = 0;
	while (g_cmd[id].cmd_name[i] != '\0')
	{
		if (is_sep(g_cmd[id].cmd_name[i]))
		{
			i = store_redirs(id, i);
		}
		else
			i++;
	}
}

void	get_redirs(void)
{
	int	i;

	i = 0;
	while (i < g_nb_cmds)
	{
		set_redirs(i);
		i++;
	}
}
