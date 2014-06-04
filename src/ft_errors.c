/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 19:04:52 by srabah-m          #+#    #+#             */
/*   Updated: 2014/03/27 19:05:00 by srabah-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doseshell.h"
#include "ft_strings.h"

void	*ft_error_null(char *err_msg)
{
	ft_putstr_fd(err_msg, 2);
	g_main_return = -1;
	return (NULL);
}

int		ft_error(char *err_msg)
{
	ft_putstr_fd(err_msg, 2);
	g_main_return = -1;
	return (-1);
}

int		ft_error_parsing(char *err_msg)
{
	ft_putstr_fd(err_msg, 2);
	return (-1);
}
