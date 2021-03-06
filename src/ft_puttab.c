/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puttab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flime <flime@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/14 12:28:54 by flime             #+#    #+#             */
/*   Updated: 2014/03/14 12:32:22 by flime            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>

static void	ft_putendl(char *s)
{
	while (*s)
		write(1, s++, 1);
	write(1, "\n", 1);
}

void		ft_puttab(char **s)
{
	while (*s)
		ft_putendl(*(s++));
}
