/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buil_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernabe <jbernabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/16 16:14:58 by jbernabe          #+#    #+#             */
/*   Updated: 2014/03/27 12:25:32 by jbernabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "shell.h"

static void				echo_no_opt(char **msh_av, char **env)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (msh_av[i] != NULL)
	{
		j = 0;
		while (msh_av[i][j] != '\0')
		{
			if (msh_av[i][j] != 34)
				write(1, &msh_av[i][j], 1);
			j++;
		}
		write(1, " ", 1);
		i++;
		free(msh_av[i]);
	}
	write(1, "\n", 1);
	(void)env;
}

static void				echo_op_n(char **msh_av, char **env)
{
	int		i;
	char	*str;
	int		len_char;

	i = 2;
	len_char = 0;
	while (msh_av[i] != NULL)
	{
		len_char += ft_strlen(msh_av[i]);
		i++;
	}
	len_char += 1;
	if (!(str = (char *)malloc(sizeof(char) * len_char)))
		return ;
	i = 2;
	while (msh_av[i] != NULL)
	{
		str = ft_strjoin_glue(str, msh_av[i], ' ');
		i++;
	}
	str[len_char + i] = '\0';
	str++;
	write(3, str, ft_strlen(str));
	write(3, "\n", 1);
	(void)env;
}

static int			set_option_echo(char *opt)
{
	if (ft_strcmp(opt, "n") == 0)
		return (1);
	return (0);
}

void				buil_echo(int ac, char **msh_av, char **env, char *opt)
{
	static void		(*echo_control[2])(char **msh_av, char **env) =
					{echo_no_opt, echo_op_n};
	int				ret;

	ret = set_option_echo(opt);
	echo_control[ret](msh_av, env);
	(void)ac;
	(void)opt;
	return ;
}
