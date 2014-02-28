/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernabe <jbernabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/24 19:06:30 by jbernabe          #+#    #+#             */
/*   Updated: 2014/02/28 19:03:01 by jbernabe         ###   ########.fr       */
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
# define TGOTO(id)	tputs(tgoto(tgetstr(#id, NULL), 1, trcs_putchar)
# define EXEC_INST	{tercs_up, tercs_down, tercs_right, tercs_left}
# define EXE_PARAM	t_command *line, t_letter *, char [8]

extern char **environ;

typedef struct s_tercs	t_tercs;

typedef struct			s_stack
{
	char				**str_tab;
	struct s_stack		*right;
	struct s_stack		*left;
}						t_stack;

typedef struct			s_command
{	
	char				*line;
	char				*path;
	char				**cmd_arg;
	size_t				index;
}						t_command;

typedef struct			s_letter
{
	char				letter;
	struct s_letter		*next;
	struct s_letter		*prev;
	size_t				cursor;
}						t_letter;

struct					s_tercs
{
	int					tty_fd;	
	t_stack				*hist;
	struct termios		term_fd;
	struct termios		term_save;
	size_t				line_len;
};

typedef struct			s_shell
{
	t_command			*data;
	t_tercs				*tcs;
	char				**env;
	char				*prompt;
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

void		show_prompt(t_shell **shell);
int			init_line(t_shell *root);

/*
**	init_types.c
*/

int			set_type(char key[8]);
int			read_key(char key[8], int fd);

/*
** tercs_init.c
*/

void		reset_term(t_shell	*root);
int			trcs_putchar(int c);
void		init_trcs(t_tercs *tcs);
int			set_fd(void);

/*
** tercs_control.c
*/

void	tercs_up(t_command *c_line, t_letter *let,  char key[8]);
void	tercs_down(t_command *c_line, t_letter *let,  char key[8]);
void	tercs_right(t_command *c_line, t_letter *let,  char key[8]);
void	tercs_left(t_command *c_line, t_letter *let,  char key[8]);

/*
** init_current_list.c
*/

void	init_ascii(t_letter **head, char key);
void	char_to_string(t_command **string, t_letter *head, char *prom);

/*
** error.c
*/

void	error_command(char *s);
int		error_fd(char *s, int fd);

/*
** debug
*/

void	display_list_test(t_letter *head);
int		ft_list_len(t_letter *head);

#endif
