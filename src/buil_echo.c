/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buil_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernabe <jbernabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/16 16:14:58 by jbernabe          #+#    #+#             */
/*   Updated: 2014/03/17 01:32:24 by jbernabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

#include <stdio.h> //

static void ft_clean(char **av)
{
	int i;

	i = 0;
	if (*av[0] == 34)
		(*av)++;
	if ((*av)[ft_strlen(*av) - 1] == 34)
		(*av)[ft_strlen(*av) - 1] = '\0';
}

static void echo_no_opt(char **msh_av, char **env)
{
	int	i;
	int	j;
	
	i = 1;
	j = 0;
	while(msh_av[i] != NULL)
	{
		ft_clean(&(msh_av[i]));
		write(1, msh_av[i], ft_strlen(msh_av[i]));
		write(1, " ", 1);
		i++;
		free(msh_av[i]);
	}
	write(1, "\n", 1);
	(void)env;
}

static void echo_op_n(char **msh_av, char **env)
{
	int			i;
	char		*str;
	int			len_char;

	i = 2;
	len_char = 0;
	while(msh_av[i] != NULL)
	{
		len_char += ft_strlen(msh_av[i]);
		i++;
	}
	len_char += 1;
	if (!(str = (char *)malloc(sizeof(char *) * len_char)))
		return ;
	i = 2;
	while (msh_av[i] != NULL)
	{
		str = ft_strjoin_glue(str, msh_av[i], ' ');
		i++;
	}
	str[len_char + i] = '\0';
	str++;
	write(3, str, ft_strlen(str) + 1);
	write(3, "\n", 1);
	(void)env;
}
/*
static int		ft_isspace(int c)
{
	if (c == ' ' || c == '\n'|| c == '\v' || c == '\f' || c == '\r'
		|| c == '\t' || c == '\b' || c == '\a')
		return (1);
}*/
//static void echo_op_e(char **msh_av, char **env)
//{

	

	

static int set_option_echo(char *opt)
{
	if (ft_strcmp(opt, "n") == 0)
		return (1);
	return (0);
}

void 		buil_echo(int ac, char **msh_av, char **env, char *opt)
{
	void	(*echo_control[2])(PARAM_ECHO) = FT_ECHO;
	int		ret;

	ret = 0;
	ret = set_option_echo(opt);
	echo_control[ret](msh_av, env);
	(void)ac;
	(void)opt;
	(void)env;
	return ;
}
