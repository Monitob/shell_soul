/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 19:21:11 by srabah-m          #+#    #+#             */
/*   Updated: 2014/03/27 19:21:53 by srabah-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doseshell.h"

char	*ft_realloc(char *cmd, int size)
{
	int		i;
	char	*new_cmd;

	i = 0;
	new_cmd = malloc(size);
	if (new_cmd == NULL)
		return (ft_error_null("Fail malloc()"));
	while (cmd[i])
	{
		new_cmd[i] = cmd[i];
		i++;
	}
	while (i < size)
		new_cmd[i++] = '\0';
	free(cmd);
	return (new_cmd);
}

char	*ft_malloc(int size)
{
	int		i;
	char	*str;

	i = 0;
	str = malloc(size);
	if (str == NULL)
		return (ft_error_null("Fail malloc"));
	while (i < size)
		str[i++] = '\0';
	return (str);
}

void	init_buf(char buf[3])
{
	buf[0] = 0;
	buf[1] = 0;
	buf[2] = 0;
}
