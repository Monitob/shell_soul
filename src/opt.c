/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_opt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flime <flime@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/14 03:18:10 by flime             #+#    #+#             */
/*   Updated: 2014/03/14 03:57:27 by flime            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h> //attention

static void	ft_putstr(char *s)
{
	while (*s)
		write (1, s++, 1);
}

static void	ft_putendl(char *s)
{
	while (*s)
		write (1, s++, 1);
	write(1, "\n", 1);
}

static void	ft_putchar(char c)
{
	write(1, &c, 1);
}

static int	opt_len(char **av);
static int	ft_strunion_len(char *av);
static char	*ft_strunion(char *av);

/*
** Returns -1 if option is invalid
** compare each unique character of *av with *option
** Returns 0 if no option;
** Returns 1 if valid
*/
char		opt_chk(char *av, char *cmd_name, char *option,  char *usage)
{
	int		i;
	int		j;
	char	*ret;
	
	if (av)
	{
		ret = av;
		i = 0;
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
char	*opt_get(char **av)
{
	int		i;
	int		j;
	int		k;
	char	*opt;

	opt = (char *)malloc(sizeof(char) * (opt_len(av) + 1));
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

/*
** Returns a string with only one iteration of each character
*/
static char	*ft_strunion(char *av)
{
	int		i;
	int		j;
	int		k;
	char	*ret;

	k = 0;
	ret = (char *)malloc(sizeof(char) * (ft_strunion_len(av) + 1));
	ret[ft_strunion_len(av)] = 1;
	i = 0;
	while (av[i])
	{
		j = 0;
		while (j < i && av[j] != av[i])
			j++;
		if (i++ == j)
			*(ret + k++) = *(av + i - 1);
	}
	ret[k] = 0;
	return (ret);
}

static int	ft_strunion_len(char *av)
{
	int		i;
	int		j;
	int		len;

	len = 0;
	i = 0;
	while (av[i])
	{
		j = 0;
		while (j < i && av[j] != av[i])
			j++;
		if (i++ == j)
			len++;
	}
	return (len);
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