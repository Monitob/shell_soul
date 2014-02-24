/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernabe <jbernabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/24 19:36:21 by jbernabe          #+#    #+#             */
/*   Updated: 2014/02/24 19:51:29 by jbernabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		show_prompt(void)
{
	int		i;
	char	**temp;

	i = 0;
	while (strncmp(environ[i], "USER=", 5) != 0)
		i++;
	temp = ft_strsplit(environ[i], '=');
	temp++;
	ft_putstr("\033[35m -> \033[0m");
	free(temp);
	temp = NULL;
	return ;
}



