/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buil_unsetenv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flime <flime@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/16 13:04:19 by flime             #+#    #+#             */
/*   Updated: 2014/03/16 13:04:23 by flime            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** csh
*/
char **buil_unsetenv(int msh_ac, char **msh_av, char **env)
{
	int		i;
	int		j;
	int		k;
	char	**ret;

	i = 1;
	if (msh_ac == 1)
		ft_putendl("unsetenv: Too few arguments.");
	else
	{
		while (msh_av[i])
		{
			j = 0;
			while (!ft_strncmp(env[j], msh_av[i], ft_strlen(msh_av[i])) && env[j])
				j++;
			if (env[j])
			{
				ret = (char **)malloc(sizeof(char *) * ft_tablen(env));
				j = 0;
				k = 0;
				while (env[j])
				{
					if (ft_strncmp(env[j], msh_av[i], ft_strlen(msh_av[i])))
					{
						ret[k] = env[j];
						k++;
					}
					j++;
				}
				ret[k] = 0;
				env = ret;
			}
			i++;
		}
	}
	return (env);
}