/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strings.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 19:13:51 by srabah-m          #+#    #+#             */
/*   Updated: 2014/03/27 21:23:51 by srabah-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_strings.h"
#include <unistd.h>

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char*)s);
		s++;
	}
	return (NULL);
}

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int		i;

	i = 0;
	while (s1[i] && s2[i] && i < n)
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	if (i == n)
	{
		return (0);
	}
	return (1);
}

int		ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 || *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	return (0);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*str;
	char	*ptr;
	int		len_s1;

	len_s1 = ft_strlen(s1);
	if (!(str = (char *)malloc(sizeof(char) * (len_s1 + ft_strlen(s2) + 1))))
		return (NULL);
	ptr = str;
	ft_strncpy(str, s1, len_s1);
	str += len_s1;
	ft_strcpy(str, s2);
	return (ptr);
}

char	*ft_strcat(char *s1, const char *s2)
{
	int		i;
	int		j;
	char	*s3;

	i = 0;
	j = 0;
	if (!(s3 = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1)))
		return (NULL);
	while (s1 && s1[i])
	{
		s3[i] = s1[i];
		i++;
	}
	while (s2[j])
		s3[i++] = s2[j++];
	s3[i] = '\0';
	return (s3);
}
