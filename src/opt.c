/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernabe <jbernabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/14 03:18:10 by flime             #+#    #+#             */
/*   Updated: 2014/03/25 00:26:36 by jbernabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "shell.h"

static int	opt_len(char **av)
{
	int		i;
	int		j;
	int		len;

	j = 1;
	len = 0;
	while (av[j] && !(av[j][0] != '-' ||
			(av[j][0] == '-' && (av[j][1] == 0 || av[j][1] == '-'))))
	{
		i = 1;
		while (*(*(av + j) + i++))
			len++;
		j++;
	}
	return (len);
}

char		opt_chk(char *av, char *cmd_name, char *option, char *usage)
{
	int		i;
	int		j;

	if (av)
	{
		i = 0;
		while (av[i++])
		{
			j = 0;
			while (option[j] && av[i - 1] != option[j])
				j++;
			if (!option[j] && usage[0] != 0)
			{
				ft_putstr(cmd_name);
				ft_putstr(": illegal option -- ");
				ft_putchar(av[i - 1]);
				ft_putchar('\n');
				ft_putendl(usage);
				return (-1);
			}
		}
		return (1);
	}
	return (0);
}

char		*opt_get(char **av)
{
	int		i;
	int		j;
	int		k;
	char	*opt;

	if (!(opt = (char *)malloc(sizeof(char) * (opt_len(av) + 1))))
		exit(0);
	k = 0;
	j = 1;
	while (av[j] && !(av[j][0] != '-' ||
			(av[j][0] == '-' && (av[j][1] == 0 || av[j][1] == '-'))))
	{
		i = 1;
		while (av[j][i])
			*(opt + k++) = *(*(av + j) + i++);
		j++;
	}
	opt[k] = 0;
	return (ft_strunion(opt));
}

int			opt_end(char **av)
{
	int		i;

	i = 1;
	while (av[i] && !(av[i][0] != '-' || (av[i][0] == '-'
		&& (av[i][1] == 0 || av[i][1] == '-'))))
		i++;
	if (av[i] && !ft_strncmp(av[i], "--", 2))
		i++;
	return (i);
}
