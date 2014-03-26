/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_space.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flime <flime@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/04 04:50:17 by flime             #+#    #+#             */
/*   Updated: 2014/02/04 12:35:48 by flime            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "shell.h"

static int	ft_wc_space(char const *s)
{
	int		wc;

	wc = 0;
	while (*s)
	{
		if (!ft_isspace(*s))
			wc++;
		while ((!ft_isspace(*s) && *s) || (*s == ' ' && *(s - 1) == '\\'))
			s++;
		while (ft_isspace(*s))
			s++;
	}
	return (wc);
}

static int	ft_fill_array_inc_wc(char c, int wc)
{
	if (!ft_isspace(c))
		wc++;
	return (wc);
}

static int	ft_fill_array_inc_i(const char *s, int i)
{
	while (ft_isspace(s[i]))
		i++;
	return (i);
}

static char	**ft_fill_array(const char *s, char **ar, int i, int wc)
{
	int		start;
	int		j;

	while (s[i])
	{
		wc = ft_fill_array_inc_wc(s[i], wc);
		start = i;
		while ((!ft_isspace(s[i]) && s[i]) || (s[i] == ' ' && s[i - 1] == '\\'))
			i++;
		ar[wc] = (char *)malloc(sizeof(char) * (i - start + 1));
		if (ar[wc] == NULL)
			return (NULL);
		j = 0;
		while (start < i)
		{
			if (s[start] == ' ' && s[start - 1] == '\\')
				*(ar[wc] + j - 1) = *(s + start++);
			else
				*(ar[wc] + j++) = *(s + start++);
		}
		ar[wc][j] = 0;
		i = ft_fill_array_inc_i(s, i);
	}
	ar[++wc] = 0;
	return (ar);
}

char		**ft_strsplit_space(char const *s)
{
	char	**ar;

	ar = (char **)malloc(sizeof(char *) * (ft_wc_space(s) + 1));
	if (ar == NULL)
		return (NULL);
	return (ft_fill_array(s, ar, 0, -1));
}
