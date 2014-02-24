/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernabe <jbernabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/24 16:17:08 by jbernabe          #+#    #+#             */
/*   Updated: 2014/02/24 19:00:23 by jbernabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

int	main(void)
{
	t_shell	*root;

	root = NULL;
	root = init_shell(root);
	root->env = init_env();
	return (0);
}

t_node		*init_shell(t_shell *root)
{
	root = (t_shell *)malloc(sizeof(*root));
	root->data = (t_command *)malloc(sizeof(*(root->data)));
	root->tcs = (t_tercs *)malloc(sizeof(*(root->tcs)));
	if (root == NULL || root->data = NULL || roots->tcs == NULL)
		error_fd("Not enought memory", 2);
	root->tcs->tty_fd = set_fd();
	return (root);
}

int			set_fd(void)
{

	int		fd;
	char	*path_fd;

	if (!(isatty(STDIN_FILENO)))
		_fd("Not a terminal", 2);
	if ((path_fd = ttyname(STDIN_FILENO)) == NULL)
		error_fd("ttayname fail", 2);
	if ((fd = open(path_fd, O_WRONLY | O_NOCTTY)) < 0)
		error_fd("open fail", 2);
	return (fd);
}

char		**init_env(void)
{
	char	**env;
	int		i;
	int		len_env;

	len_env = ft_tab_len(environ);
	env = (char **)malloc(sizeof(char **) * len_env);
	i = 0;
	while (i < len_env)
	{
		env[i] = (char *)malloc(sizeof(char *) * ft_strlen(environ[i]) + 1);
		ft_strcpy(env[i], environ[i]);
		i++;
	}
	env[i] = NULL;
	return (env);
}
	
int		error_fd(char *s, int fd)
{
		ft_putstr_fd(s, fd);
		ft_putchar('\n');
		_exit(1);
}
