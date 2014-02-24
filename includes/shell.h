/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernabe <jbernabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/24 19:06:30 by jbernabe          #+#    #+#             */
/*   Updated: 2014/02/24 19:22:48 by jbernabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <dirent.h>
# include <termios.h>
# include <signal.h>
# include <termcap.h>
# include <sys/stat.h>
# include <sys/types.h>
# include "libft.h"

# define BUFFER_R 5

extern char **environ;


typedef struct			s_stack
{
	char				*hist;
	struct s_stack		*next;
	struct s_stack		*prev;
}						t_stack;

typedef struct			s_command
{	
	char				*line;
	char				*path;
	char				**cmd_arg;
	char				buffer[BUFFER_R];
}						t_command;

typedef struct			s_tercs
{
	int					tty_fd;
	t_stack				*hist;
	struct termios		term_fd;
	struct termios		term_save;
	size_t				cursor;
	size_t				line_len;
}						t_tercs;

typedef struct			s_shell
{
	t_command			*data;
	t_tercs				*tcs;
	char				**env;
}						t_shell;

/*
 * init_shell.c
 */

t_shell		*init_shell(t_shell *root);
char		**init_env(void);
int			set_fd(void);
int			error_fd(char *s, int fd);
	
#endif
