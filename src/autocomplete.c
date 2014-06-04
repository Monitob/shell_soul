/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 18:30:04 by srabah-m          #+#    #+#             */
/*   Updated: 2014/03/27 21:40:41 by srabah-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doseshell.h"

char	*g_operators[] =
{
	PIPE,
	AND,
	OR,
	CMD_SEP,
	NULL,
	REDI_RIGHT,
	REDI_LEFT,
	REDI_D_RIGHT,
	REDI_D_LEFT,
	NULL
};

char	*extract_cmd(char *cmd)
{
	int	i;
	int	j;

	i = ft_strlen(cmd) - 1;
	while (i > 0)
	{
		j = 0;
		while (g_operators[j])
		{
			if (ft_strncmp(g_operators[j], cmd + i, ft_strlen(g_operators[j]))
				== 0)
			{
				i += ft_strlen(g_operators[j]);
				while (cmd[i] == ' ' || cmd[i] == '\t')
					i++;
				return (cmd + i);
			}
			j++;
		}
		i--;
	}
	return (cmd);
}

int		get_nb_words(char *cmd)
{
	int	i;
	int	nbr_words;

	i = 0;
	nbr_words = 0;
	while (cmd[i])
	{
		while (cmd[i] == ' ' || cmd[i] == '\t')
			++i;
		if (cmd[i])
		{
			nbr_words++;
			while (cmd[i] && cmd[i] != ' ' && cmd[i] != '\t')
				++i;
		}
	}
	return (nbr_words);
}

char	*get_last_word(char *cmd)
{
	int	i;

	i = ft_strlen(cmd) - 1;
	while (i > 0)
	{
		if (cmd[i] == ' ' || cmd[i] == '\t')
			return (cmd + i + 1);
		--i;
	}
	return (cmd);
}

int		autocomplete(char buf[3], char **cmd, int *i, t_shell *shell)
{
	int		ret;
	int		nbr_words;
	char	*cmd_bloc;

	(void)buf;
	cmd_bloc = extract_cmd(*cmd);
	nbr_words = get_nb_words(cmd_bloc);
	cmd_bloc = get_last_word(cmd_bloc);
	if (nbr_words == 0)
		ret = display_cur_dir();
	else if (nbr_words == 1)
		ret = display_bin(cmd_bloc, shell);
	else
		ret = display_path(cmd_bloc);
	display_prompt();
	ft_putstr_fd(*cmd, 1);
	*i = ft_strlen(*cmd) + 1;
	return (ret);
}
