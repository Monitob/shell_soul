/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tercs_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernabe <jbernabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/25 02:51:39 by jbernabe          #+#    #+#             */
/*   Updated: 2014/02/26 13:34:13 by jbernabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	tercs_up(t_shell *shell, char key[8])
{
	ft_putstr("go up");
}

void	tercs_ascii(t_shell *shell, char key[8])
{
	/*Get the line*/
	write(1, key, 1);

}

void	tercs_down(t_shell *shell, char key[8])
{
		ft_putstr("down");
}

void	tercs_right(t_shell *shell, char key[8])
{

		ft_putstr("up");
}

void	tercs_left(t_shell *shell, char key[8])
{
	ft_putstr("left");
}
