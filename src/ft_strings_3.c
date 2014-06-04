/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strings_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 19:17:01 by srabah-m          #+#    #+#             */
/*   Updated: 2014/03/27 21:23:24 by srabah-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_strings.h"

char	*ft_strcat_redi(char *str1, char *str2)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	j = 0;
	new_str = malloc(ft_strlen(str1) + ft_strlen(str2) + 1);
	if (new_str == NULL)
		return (NULL);
	while (str1 && str1[i])
	{
		new_str[i] = str1[i];
		i++;
	}
	while (str2[j])
		new_str[i++] = str2[j++];
	new_str[i] = '\0';
	free(str1);
	return (new_str);
}

char	*ft_strndup(char *str, int len)
{
	int		i;
	char	*new_str;

	i = -1;
	if (!(new_str = (char *)malloc(sizeof(char) * (len + 1))))
		return (ft_error_null("Couldn't malloc\n"));
	while (++i < len && str[i] != '\0')
		new_str[i] = str[i];
	new_str[i] = '\0';
	return (new_str);
}
