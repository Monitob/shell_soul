/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flime <flime@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/11 07:35:00 by flime             #+#    #+#             */
/*   Updated: 2014/03/11 07:49:32 by flime            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <string.h>
#include <stdlib.h>

char	*ft_strndup(const char *s1, size_t n)
{
	char	*ret;
	size_t	i;

	i = 0;
	ret = (char *)malloc(sizeof(char) * (n + 1));
	if (ret != NULL)
	{
		while (i < n && s1[i])
		{
			ret[i] = s1[i];
			i++;
		}
		ret[i] = 0;
	}
	return (ret);
}
