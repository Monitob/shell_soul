/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strings_4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 19:14:58 by srabah-m          #+#    #+#             */
/*   Updated: 2014/03/27 21:24:34 by srabah-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_strings.h"
#include <unistd.h>

size_t	ft_strlen(const char *s)
{
	const char	*ptr;

	ptr = s;
	while (*ptr)
		ptr++;
	return (ptr - s);
}

char	*ft_strcpy(char *s1, const char *s2)
{
	char	*ptr;

	ptr = s1;
	while (*s2)
	{
		*s1++ = *s2++;
	}
	*s1 = '\0';
	return (ptr);
}

char	*ft_strncpy(char *s1, const char *s2, size_t n)
{
	char	*ptr;

	ptr = s1;
	while (*s2 && n-- > 0)
		*s1++ = *s2++;
	while (n-- > 0)
		*s1++ = '\0';
	return (ptr);
}

void	ft_putchar(const char c)
{
	write(1, &c, 1);
}

void	ft_putstr(const char *s)
{
	write(1, s, ft_strlen(s));
}
