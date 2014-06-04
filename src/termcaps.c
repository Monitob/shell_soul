/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 20:17:24 by srabah-m          #+#    #+#             */
/*   Updated: 2014/03/27 20:48:51 by srabah-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doseshell.h"

t_char	g_arrow_manage[] =
{
	{ARROW, check_arrow},
	{CTRLD, ctrl_termcaps},
	{CTRLL, ctrl_termcaps},
	{BACKSPACE, backspace_termcaps},
	{TAB, autocomplete},
	{-1, add_char}
};

int		check_cmd(char buf[3], char **cmd, int *i, t_shell *shell)
{
	int	j;

	j = 0;
	while (g_arrow_manage[j].value != -1 && buf[0] != g_arrow_manage[j].value)
		j++;
	return (g_arrow_manage[j].fct_ptr(buf, cmd, i, shell));
}

int		check_for_realloc(char **cmd, int size)
{
	if ((int)(ft_strlen(*cmd) + 2) >= (int)size)
	{
		if (((*cmd) = ft_realloc(*cmd, size + 1024)) == NULL)
			return (ft_error("Fail malloc"));
		size += 1024;
	}
	return (size);
}

char	*termcaps_prompt(t_shell *shell)
{
	int		ret;
	char	buf[3];

	g_prompt.size = 1024;
	g_prompt.i = 1;
	if ((g_prompt.cmd = ft_malloc(1024)) == NULL)
		return (NULL);
	init_buf(buf);
	while ((ret = read(0, buf, 3) > 0))
	{
		if ((g_prompt.size = check_for_realloc(&(g_prompt.cmd),
			g_prompt.size)) == -1)
			return (NULL);
		if (buf[0] == '\n')
			return (g_prompt.cmd);
		else if (check_cmd(buf, &(g_prompt.cmd), &(g_prompt.i), shell) == -1)
			return (NULL);
		init_buf(buf);
	}
	if (ret == -1)
		return (ft_error_null("fail read"));
	g_prompt.cmd[0] = '\0';
	return (g_prompt.cmd);
}
