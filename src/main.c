/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 20:02:19 by srabah-m          #+#    #+#             */
/*   Updated: 2014/03/27 22:08:55 by jbernabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doseshell.h"

int			g_is_a_term;
int			g_main_return;
t_prompt	g_prompt;

int		parsexec(char *cmd, t_shell *shell)
{
	int		ret;
	t_cmd	*cmd_data;
	t_tree	*cmd_tree;

	g_is_a_term = 0;
	if ((cmd = add_some_space(cmd)) == NULL
		|| (cmd_data = get_cmd_data(cmd)) == NULL)
		return (-1);
	lexing(cmd_data);
	if ((ret = replace_var(cmd_data, shell)) != -1
		&& ret != -2 && parsing(cmd_data))
	{
		if ((cmd_tree = get_tree(cmd_data)) == NULL
			|| exec_tree(cmd_tree, shell) == -1)
			return (-1);
		clean_memory(cmd_tree, cmd_data, cmd);
	}
	return (ret);
}

int		doseshell(t_shell *shell, int tty)
{
	char	*cmd;

	signal(SIGINT, sig_manage);
	while ((cmd = get_cmd_input(shell, tty)))
		if ((tty && exit_raw_mode() == -1)
			|| parsexec(cmd, shell) == -1)
			return (-1);
	return (g_main_return);
}

void	clean_shell_mem(t_shell *shell)
{
	int		i;
	t_env	*tmp;

	i = 0;
	while (shell->path && shell->path[i++])
		free(shell->path[i - 1]);
	free(shell->path);
	tmp = shell->env->next;
	while (tmp != shell->env)
	{
		tmp = tmp->next;
		free(tmp->prev->var);
		free(tmp->prev);
	}
	free(tmp);
	tmp = shell->his->next;
	while (tmp != shell->his)
	{
		tmp = tmp->next;
		free(tmp->prev->var);
		free(tmp->prev);
	}
	free(tmp);
	free(shell);
}

int		main(int ac, char **av, char **env)
{
	int		tty;
	t_shell	*shell;

	(void)ac;
	(void)av;
	tty = isatty(0);
	g_is_a_term = tty;
	ft_putstr("\x1b[32mDoseShell\x1b[35m");
	ft_putstr(", by flime, jbernabe, srabah-m\x1b[0m \n\n");
	if ((shell = init_shell(env, &tty)) == NULL)
		return (-1);
	doseshell(shell, tty);
	clean_shell_mem(shell);
	return (g_main_return);
}
