/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 19:04:32 by srabah-m          #+#    #+#             */
/*   Updated: 2014/03/27 19:04:47 by srabah-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doseshell.h"

int		my_env(t_cmd *cmd, t_shell *shell)
{
	t_env		*tmp;

	(void)cmd;
	tmp = shell->env->next;
	while (tmp != shell->env)
	{
		ft_putstr_fd(tmp->var, 1);
		ft_putchar('\n');
		tmp = tmp->next;
	}
	return (1);
}
