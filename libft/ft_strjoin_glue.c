/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_glue.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernabe <jbernabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/28 18:38:36 by jbernabe          #+#    #+#             */
/*   Updated: 2014/02/08 21:04:19 by jbernabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_strjoin_glue(char *s1, char *s2, char c)
{
		char		*new_string;
		size_t		len;

		if (s1)
		{
				len = ft_strlen(s1);
				new_string = s1;
				s1 = (char *)malloc((len + 2) * sizeof(char));
				ft_strcpy(s1, new_string);
				s1[len] = c;
				s1[len + 1] = '\0';
				new_string = ft_strjoin(s1, s2);
				free(s1);
				return (new_string);
		}
		return (NULL);
}
