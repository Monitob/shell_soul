/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabidx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flime <flime@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/16 13:29:56 by flime             #+#    #+#             */
/*   Updated: 2014/03/16 13:29:57 by flime            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

static int	ft_strncmp(char const *str1, char const *str2, size_t len)
{
	int	result;
	int	i;

	i = 1;
	result = 0;
	while ((*str1 == *str2) && (*str1 != '\0') && (i < (int) len))
	{
		str1++;
		str2++;
		i++;
	}
	if (len > 0)
		result = (unsigned char) *str1 - (unsigned char) *str2;
	return (result);
}

/*
** If s is included in t, then ft_tabidx returns the matching index
** otherwise the function returns -1
*/
int			ft_tabidx(char **t, char *s, int len)
{
	int		i;

	i = 0;
	while (t[i])
	{
		if (!ft_strncmp(t[i], s, len))
			return (i);
		i++;
	}
	return (-1);
}