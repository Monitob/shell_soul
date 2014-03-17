/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flime <flime@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/14 03:18:10 by flime             #+#    #+#             */
/*   Updated: 2014/03/16 16:35:49 by jbernabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "shell.h"

static int	opt_len(char **av);

/*
** Returns -1 if option is invalid
** compare each unique character of *av with *option
** Returns 0 if no option;
** Returns 1 if valid
*/
char		opt_chk(char *av, char *cmd_name, char *option, char *usage)
{
	int		i;
	int		j;
	char	*ret;

	if (av)
	{
		ret = av + (i = 0);
		while (ret[i++])
		{
			j = 0;
			while (option[j] && ret[i - 1] != option[j])
				j++;
			if (!option[j] && usage[0] != 0) //reduire le message. pour les lignes
			{
				ft_putstr(cmd_name);
				ft_putstr(": illegal option -- ");
				ft_putchar(ret[i - 1]);
				ft_putchar('\n');
				ft_putendl(usage);
				return (-1);
			}
		}
		return (1);
	}
	return (0);
}

/*
** Returns a copy of av stopped when "--" or  "X"
** where X is different from '-'
** with with one iteration of each option.
*/
char		*opt_get(char **av)
{
	int		i;
	int		j;
	int		k;
	char	*opt;

	if (!(opt = (char *)malloc(sizeof(char) * (opt_len(av) + 1))))
		exit(0);
	k = 0;
	j = 1; //a verifier si 1 ou 2;
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

int			opt_end(char **av/*, char *option*/)
{
	int		i;
	// size_t	j;
	// int		chk;

	i = 1;
//	chk = 0;
	while (av[i] && !(av[i][0] != '-' || (av[i][0] == '-'
						&& (av[i][1] == 0 || av[i][1] == '-'))))
	{
		// j = 0;
		// chk = 0;
		// while (option[j])
		// {
		// 	ft_putchar(option[j]);
		// 	ft_putchar('\n');
		// 	if (ft_strchr(av[i], option[j]) != NULL)
		// 	{
		// 		ft_putendl("option");
		// 		chk = 1;
		// 	}
		// 	j++;
		// }
		// if (chk == 0)
		// 	break ;
		i++;
	}
	if (av[i] && !ft_strncmp(av[i], "--", 2))
		i++;
	return (i);
}



/*int		main(int ac, char **av)
{
	char	usage[] = "usage: ls [-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1] [file ...]";

	(void)ac;
	if ((opt_chk(av, "ls", "ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1", usage)) != NULL)
		ft_putendl(opt_chk(av, "ls", "ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1", usage));
	else
		ft_putendl("NULL");
	return (0);
}
*/
/*
int		main(int ac, char **av)
{
	printf("%d\n", opt_end(av, "PL"));
	printf("%s\n", av[opt_end(av, "PL"));
	return (0);
}
*/