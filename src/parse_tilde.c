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
#include <sys/errno.h>

int		parse_tilde(char **s, char **env)
{
	int		i;
	char	*pwd;
	char	*tmp;

	i = 0;
	pwd = env_rmname(env, "PWD=");
	while (s[i])
	{
		if (!ft_strncmp(s[i], "~+", 2))
			s[i] = env_rmname(env, "PWD=");
		else if (!ft_strncmp(s[i], "~-", 2))
			s[i] = env_rmname(env, "OLDPWD=");
		else if (!ft_strncmp(s[i], "~/", 2))
			s[i] = ft_strjoin(env_rmname(env, "HOME="), ft_strsub(s[i], 1, ft_strlen(s[i])));
		else if (!ft_strncmp(s[i], "~", 1) && ft_strcmp(s[i], "~"))
		{
			tmp = ft_strndup(env_rmname(env, "HOME="),
				ft_strlen(env_rmname(env, "HOME=")) - ft_strlen(env_rmname(env, "USER=")));
			tmp = ft_strjoin(tmp, ft_strsub(s[i], 1, ft_strlen(s[i])));
			if (chdir(tmp))
			{
				ft_putstr("42sh: ");
				ft_putstr(strerror(errno));//check error
				ft_putstr(" : "); 
				ft_putendl(ft_strsub(s[i], 1, ft_strlen(s[i])));
				chdir(pwd);
				return (-1);
			}
			else
				s[i] = tmp;
		}
		else if (!ft_strcmp(s[i], "~"))
			s[i] = env_rmname(env, "HOME=");
		i++;
	}
	return (0);
}
// 	int		main(int ac, char **av, **env)
// {
// 	printf("%d\n", parse_tilde(av[1], env));
// 	return (0);
// }
