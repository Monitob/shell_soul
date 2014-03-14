/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tablen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernabe <jbernabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/14 19:52:33 by jbernabe          #+#    #+#             */
/*   Updated: 2014/02/05 04:43:02 by jbernabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_tab_len(char **tb)
{
	int	i;

	i = 0;
	if (tb == NULL)
		return (0);
	while (tb[i] != NULL)
		i++;
	return (i);
}
