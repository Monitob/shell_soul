/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rep_history.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 20:19:39 by srabah-m          #+#    #+#             */
/*   Updated: 2014/03/27 21:08:47 by srabah-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doseshell.h"

int	ft_get_nb(char *str)
{
	int	sign;
	int	nb;

	sign = 1;
	if (!str)
		return (0);
	while (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	nb = 0;
	while (*str >= '0' && *str <= 9)
	{
		nb *= 10;
		nb += (*str - '0');
	}
	return (nb * sign);
}

int	revnum_f(t_cmd *tmp, t_env *his)
{
	char	*cpy;
	t_cmd	*replace;
	t_env	*tmp_his;
	int		num_to_search;

	tmp_his = his->prev->prev;
	num_to_search = his->prev->num - ft_get_nb(tmp->word + 2);
	while (tmp_his != his)
	{
		if (tmp_his->num == num_to_search)
		{
			if ((cpy = ft_strdup(tmp_his->var)) == NULL
				|| (replace = get_cmd_data(cpy)) == NULL)
				return (-1);
			return (replace_cmd(tmp, tmp_his, his, replace));
		}
		tmp_his = tmp_his->prev;
	}
	ft_putstr("Error, last event not found\n");
	return (-2);
}

int	num_f(t_cmd *tmp, t_env *his)
{
	char	*cpy;
	t_cmd	*replace;
	t_env	*tmp_his;
	int		num_to_search;

	tmp_his = his->next;
	num_to_search = ft_get_nb(tmp->word + 1);
	while (tmp_his != his->prev)
	{
		if (tmp_his->num == num_to_search)
		{
			if ((cpy = ft_strdup(tmp_his->var)) == NULL
				|| (replace = get_cmd_data(cpy)) == NULL)
				return (-1);
			return (replace_cmd(tmp, tmp_his, his, replace));
		}
		tmp_his = tmp_his->next;
	}
	ft_putstr("Error, last event not found\n");
	return (-2);
}
