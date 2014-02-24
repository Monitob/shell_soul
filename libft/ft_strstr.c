/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernabe <jbernabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/27 18:15:37 by jbernabe          #+#    #+#             */
/*   Updated: 2013/12/01 20:58:24 by jbernabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *s1, const char *s2)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!s1)
		return (NULL);
	if (*(s2) == '\0')
		return ((char *)s1);
	while ((*(s1 + i) != '\0'))
	{
		j = 0;
		while ((*(s1 + i + j ) == s2[j]) && (s2[j] != '\0'))
		{
			j++;
		}
		if (*(s2 + j) == '\0')
		{
			return ((char *)(s1 + i));
		}
		i++;
	}
	return (NULL);
}
