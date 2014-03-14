/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chkenv_name.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flime <flime@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/13 09:37:39 by flime             #+#    #+#             */
/*   Updated: 2014/03/13 11:44:58 by flime            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_strlen(char *s);
/*static int	ft_count_chr(char *s, char c);*/

/*
** Format the environement name
*/
char	*ft_chkenv_name(char *s) //revoir les mallocs c sale
{
	int		i;
	char	*ret;
	char	test;

	ret = (char *)malloc(sizeof(char) *
								(ft_strlen(s) /*- ft_count_chr(s, c)*/ + 1));
	i = 0;
	test = 0;
	while (*s)
	{
		if (*s == '=' && test == 0) //faire une fonction seule;
			return (NULL);
		else if (*s != '\\')
		{
			*(ret + i++) = *(s);
			test = 0;
		}
		else if (*s == '\\' && test == 0)
			test = 1;
		else if (*s == '\\' && test == 1)
		{
			*(ret + i++) = *(s);
			test = 0;
		}
		s++;
	}
	ret[i] = 0;
	return (ret);
}

static int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		++i;
	return (i);
}

/*static int	ft_count_chr(char *s, char c)
{
	int		ret;

	ret = 0;
	while (*s)
	{
		if (*(s++) == c)
			++ret;
	}
	return (ret);
}*/
