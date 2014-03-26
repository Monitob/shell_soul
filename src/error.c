/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernabe <jbernabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/28 14:51:11 by jbernabe          #+#    #+#             */
/*   Updated: 2014/02/28 14:59:27 by jbernabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	error_command(char *s)
{
	ft_putendl(s);
	exit(0);
}

int		error_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	ft_putchar('\n');
	exit(1);
}
