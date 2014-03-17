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

static char	**ft_fill_array(char const *s, char **ar)
{
	int		wc;
	int		start;
	int		i;
	int		j;

	wc = (i = 0) -1;
	while (s[i])
	{
		if (!ft_isspace(s[i]))
			wc++;
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
			{
				*(ar[wc] + j - 1) = *(s + start);
				start++;
			}
			else
				*(ar[wc] + j++) = *(s + start++);
		}
		ar[wc][j] = 0;
		while (ft_isspace(s[i]))
			i++;
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
	return (ft_fill_array(s, ar));
}
