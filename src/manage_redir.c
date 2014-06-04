/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 19:58:56 by srabah-m          #+#    #+#             */
/*   Updated: 2014/03/27 20:56:04 by srabah-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doseshell.h"

int		redi_right(char *file, t_shell *shell)
{
	static int	fd = 0;

	(void)shell;
	if (fd && fd != -1)
		close(fd);
	fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_putstr_fd(file, 1);
		ft_putstr_fd(": No such file or directory.\n", 1);
		return (0);
	}
	if (dup2(fd, 1) == -1)
		return (ft_error("Couldn't dup2\n"));
	return (0);
}

int		redi_d_right(char *file, t_shell *shell)
{
	static int	fd = 0;

	(void)shell;
	if (fd && fd != -1)
		close(fd);
	fd = open(file, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd == -1)
	{
		ft_putstr_fd(file, 1);
		ft_putstr_fd(": No such file or directory.\n", 1);
		return (0);
	}
	if (dup2(fd, 1) == -1)
		return (ft_error("Coudn't dup2\n"));
	return (0);
}

int		redi_left(char *file, t_shell *shell)
{
	static int	fd = 0;

	(void)shell;
	if (fd && fd != -1)
		close(fd);
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd(file, 1);
		ft_putstr_fd(": No such file or directory.\n", 1);
		return (-2);
	}
	if (dup2(fd, 0) == -1)
		return (ft_error("fail dup2"));
	return (0);
}

int		write_and_read_redi_d_left(char *buffer)
{
	int	i;
	int	pid;
	int	pipe_fd[2];

	i = 0;
	if (pipe(pipe_fd) == -1
		|| (pid = fork()) == -1)
		return (ft_error("fail fork / pipe\n"));
	if (pid)
	{
		close(pipe_fd[1]);
		if (dup2(pipe_fd[0], 0) == -1)
			return (ft_error("fail dup2\n"));
		return (0);
	}
	else
	{
		while (buffer[i])
		{
			write(pipe_fd[1], buffer + i, 1);
			i++;
		}
		return (-1);
	}
}

int		redi_d_left(char *key_word, t_shell *shell)
{
	int		size;
	char	*str;
	char	*buffer;

	size = 1024;
	if ((buffer = malloc(size)) == NULL)
		return (ft_error("fail malloc\n"));
	buffer[0] = '\0';
	ft_putstr_fd("? ", shell->store_io[1]);
	while ((str = get_next_line(0)) && !ft_strcmp(str, key_word))
	{
		while ((int)(ft_strlen(buffer) + ft_strlen(str) + 2) >= (int)size)
		{
			size += 1024;
			if ((buffer = ft_realloc(buffer, size)) == NULL)
				return (-1);
		}
		if ((buffer = ft_strcat_redi(buffer, str)) == NULL
			|| (buffer = ft_strcat_redi(buffer, "\n")) == NULL)
			return (-1);
		ft_putstr_fd("? ", shell->store_io[1]);
		free(str);
	}
	return (write_and_read_redi_d_left(buffer));
}
