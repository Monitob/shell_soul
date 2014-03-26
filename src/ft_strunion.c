/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strunion.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flime <flime@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/16 14:28:45 by flime             #+#    #+#             */
/*   Updated: 2014/03/16 14:28:47 by flime            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_strunion_len(char *av)
{
	int		i;
	int		j;
	int		len;

	len = 0;
	i = 0;
	while (av[i])
	{
		j = 0;
		while (j < i && av[j] != av[i])
			j++;
		if (i++ == j)
			len++;
	}
	return (len);
}

char		*ft_strunion(char *av)
{
	int		i;
	int		j;
	int		k;
	char	*ret;

	k = 0;
	ret = (char *)malloc(sizeof(char) * (ft_strunion_len(av) + 1));
	ret[ft_strunion_len(av)] = 1;
	i = 0;
	while (av[i])
	{
		j = 0;
		while (j < i && av[j] != av[i])
			j++;
		if (i++ == j)
			*(ret + k++) = *(av + i - 1);
	}
	ret[k] = 0;
	return (ret);
}
