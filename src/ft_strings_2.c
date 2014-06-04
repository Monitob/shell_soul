/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strings_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 19:16:48 by srabah-m          #+#    #+#             */
/*   Updated: 2014/03/27 21:23:33 by srabah-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_strings.h"

int		is_space(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int		is_sep(char c)
{
	if ((c == '|') || (c == '>') || (c == '<'))
		return (1);
	else
		return (0);
}

int		is_sep_space(char c)
{
	if (is_space(c))
		return (1);
	else if (is_sep(c))
		return (1);
	return (0);
}
