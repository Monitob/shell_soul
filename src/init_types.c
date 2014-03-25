/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_types.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernabe <jbernabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/05 15:54:00 by jbernabe          #+#    #+#             */
/*   Updated: 2014/03/24 17:18:29 by jbernabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			read_key(char key[8], int fd)
{
	int		type;

	type = 0;
	ft_memset(key, 0, 8);
	if (read(fd, key, BUFFER_R) < 0)
		return (-2);
	type = set_type(key);
	return (type);
}

/*On a le droit de faire ca?????????????????
char key[8]??????
*/
static int	set_type_next(char key[8])
{
	if 		(key[0] == 27 && key[1] == 27 && key[2] == 91)
	{
		if (key[3] == 65)
		{
			ft_putstr("alt up  defined");
			return (-2);
		}
		if (key[3] == 66)
		{
			ft_putstr("alt up  down");
			return (-2);
		}
		if (key[3] == 67)
		{
			ft_putstr("alt up  right");
			return (-2);
		}
		if (key[3] == 68)
		{
			ft_putstr("alt up  left");
			return (-2);
		}
	}
	if		(key[0] == 127)
	{
		ft_putstr("del  left");
		return (-2);
	}
	if		(key[0] == 12)
	{
		ft_putstr("clear");
		return (-2);
	}
	if		(key[0] == 13)
	{
		return (RETURN);
	}
	return (-2);
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
		if 	(key[2] == 72)
		{
			ft_putstr("home not defined");
			return (-2);
		}
	}
	return (set_type_next(key));
}
