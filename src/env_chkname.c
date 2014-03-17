/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_chkname.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flime <flime@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/13 09:37:39 by flime             #+#    #+#             */
/*   Updated: 2014/03/13 11:44:58 by flime            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shell.h>

/*static int	ft_count_chr(char *s, char c);*/

/*
** Format the environement name
*/
char	*env_chkname(char *s)
{
	int		i;
	char	*ret;
	char	test;

	ret = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	i = 0;
	test = 0;
	while (*s)
	{
		if (*s == '=' && test == 0)
			return (NULL);
		else if (*s != '\\' || (*s == '\\' && test == 1))
		{
			*(ret + i++) = *(s);
			test = 0;
		}
		else if (*s == '\\' && test == 0)
			test = 1;
		s++;
	}
	ret[i] = 0;
	return (ret);
}
