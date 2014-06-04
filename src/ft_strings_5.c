/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strings_5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 19:16:24 by srabah-m          #+#    #+#             */
/*   Updated: 2014/03/27 21:22:57 by srabah-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_strings.h"
#include <unistd.h>

void	ft_putstr_fd(const char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}

void	ft_putendl(const char *s)
{
	ft_putstr(s);
	ft_putstr("\n");
}

char	*ft_strdup(const char *s1)
{
	const char	*ptr;
	char		*ptr2;
	char		*cpy;

	ptr = s1;
	while (*ptr)
		ptr++;
	if (!(cpy = (char *)malloc(sizeof(char) * (ptr - s1 + 1))))
		return (NULL);
	ptr2 = cpy;
	while (*s1)
		*cpy++ = *s1++;
	*cpy = '\0';
	return (ptr2);
}
