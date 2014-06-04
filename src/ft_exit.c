/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 19:06:38 by srabah-m          #+#    #+#             */
/*   Updated: 2014/03/27 21:30:13 by srabah-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doseshell.h"

int	my_exit(t_cmd *cmd, t_shell *shell)
{
	(void)shell;
	if (cmd->next->next != cmd)
		g_main_return = ft_get_nb(cmd->next->next->word);
	else
		g_main_return = 0;
	ft_putstr("Exit [");
	ft_putchar(g_main_return + '0');
	ft_putstr("]\n");
	return (-1);
}
