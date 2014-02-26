/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_types.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernabe <jbernabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/26 11:08:59 by jbernabe          #+#    #+#             */
/*   Updated: 2014/02/26 12:28:10 by jbernabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		read_key(char key[8], int fd)
{
	ft_bzero(key, 9);
	read(fd, key, BUFFER_R);
}

int			set_type(char key[8])
{
	if (key[0] == 27 && key[1] == 91)
	{
		if	(key[2] == 65)
			return (UP);
		if	(key[2] == 66)
			return (DOWN);
		if	(key[2] == 67)
			return (RIGHT);
		if	(key[2] == 68)
			return (LEFT);
	}
	if (key[0] == 10)
		return (RETURN);
	return (-2);
}
