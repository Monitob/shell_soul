/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/24 18:25:04 by srabah-m          #+#    #+#             */
/*   Updated: 2014/01/24 18:50:25 by srabah-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mnsh.h>

void	ft_fatal(char *error_msg)
{
	ft_putstr_fd(error_msg, 2);
	ft_putstr_fd("\n", 2);
	exit(1);
}
