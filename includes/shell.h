/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernabe <jbernabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/24 19:06:30 by jbernabe          #+#    #+#             */
/*   Updated: 2014/02/26 13:30:15 by jbernabe         ###   ########.fr       */
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
# include <term.h>
# include <sys/stat.h>
# include <sys/types.h>
# include "libft.h"

# define BUFFER_R	8	
# define TPUTS(id)	tputs(tgetstr(#id, NULL), 1, trcs_putchar)
# define EXEC_INST	{tercs_ascii, tercs_up, tercs_down, tercs_right, tercs_left}

extern char **environ;

typedef struct s_tercs	t_tercs;

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
	t_tercs				*curr_hist;
}						t_command;

struct					s_tercs
{
	int					tty_fd;
	t_stack				*hist;
	struct termios		term_fd;
	struct termios		term_save;
	size_t				cursor;
	size_t				line_len;
};

typedef struct			s_shell
{
	t_command			*data;
	t_tercs				*tcs;
	char				**env;
}						t_shell;

enum					e_key
{
	RETURN = -1, ASCII = 0, UP = 1, DOWN = 2,
	RIGHT = 3, LEFT = 4
};

/*
** init_shell.c
*/

t_shell		*init_shell(t_shell *root);
char		**init_env(void);

/*
** init_shell2.c
*/

void		show_prompt(void);
int			init_line(t_shell *root);

/*
**	init_types.c
*/

int			set_type(char key[8]);
void		read_key(char key[8], int fd);

/*
** tercs_init.c
*/

void		reset_term(t_shell	*root);
int			trcs_putchar(int c);
void		init_trcs(t_tercs *tcs);
int			set_fd(void);
int			error_fd(char *s, int fd);

/*
** tercs_control.c
*/

void	tercs_up(t_shell *shell, char key[8]);
void	tercs_ascii(t_shell *shell, char key[8]);
void	tercs_down(t_shell *shell, char key[8]);
void	tercs_right(t_shell *shell, char key[8]);
void	tercs_left(t_shell *shell, char key[8]);

#endif
