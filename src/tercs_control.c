/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tercs_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernabe <jbernabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/25 02:51:39 by jbernabe          #+#    #+#             */
/*   Updated: 2014/02/26 11:52:28 by jbernabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	tercs_up(t_shell *shell, char key[8])
{
	ft_putstr("go up");
}

void	tercs_ascii(t_shell *shell, char key[8])
{

}

void	tercs_down(t_shell *shell, char key[8])
{
		ft_putstr("down");
}

void	tercs_right(t_shell *shell, char key[8])
{

		ft_putstr("up");
}
