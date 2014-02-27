/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tercs_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernabe <jbernabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/25 02:51:39 by jbernabe          #+#    #+#             */
/*   Updated: 2014/02/26 14:27:42 by jbernabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	tercs_up(t_shell *shell, char key[8])
{
	if (!shell->tcs->hist)
		return ;
	if (shell->tcs->cursor)
	{
		ft_putstr("go up");
	}
	(void)key;
}

void	tercs_ascii(t_shell *shell, char key[8])
{
	if (shell)
	{
		write(1, key, 1);
	}
	(void)key;
}

void	tercs_down(t_shell *shell, char key[8])
{
	if (shell->tcs->cursor)
	{
		ft_putstr("down");

	}
	(void)key;
}

void	tercs_right(t_shell *shell, char key[8])
{
	if (shell->tcs->cursor < shell->tcs->line_len)
	{
		shell->tcs->cursor += 1;
		TPUTS(nd);
		ft_putstr("up");
	}
	(void)key;
}

void	tercs_left(t_shell *shell, char key[8])
{
	if (shell->tcs->cursor)
	{
		shell->tcs->cursor -= 1;
		TPUTS(le);
		ft_putstr("left");
	}
	(void)key;
}
