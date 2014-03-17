/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tilde.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flime <flime@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/17 03:07:27 by flime             #+#    #+#             */
/*   Updated: 2014/03/17 03:34:04 by flime            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	parse_tilde(char **s, char **env)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (!ft_strcmp(s[i], "~"))
			s[i] = env_rmname(env, "HOME=");
		else if (!ft_strncmp(s[i], "~/", 2))
			s[i] = ft_strjoin(env_rmname(env, "HOME="), ft_strsub(s[i], 2, ft_strlen(s[i])));
		i++;
	}
}
// 	int		main(int ac, char **av, **env)
// {
// 	printf("%d\n", parse_tilde(av[1], env));
// 	return (0);
// }
