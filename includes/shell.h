/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernabe <jbernabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/24 19:06:30 by jbernabe          #+#    #+#             */
/*   Updated: 2014/03/26 19:19:05 by jbernabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include <stdlib.h>
# include <dirent.h>
# include <termios.h>
# include <signal.h>
# include <term.h>
# include <sys/stat.h>
# include <sys/types.h>
# include "libft.h"
# include "buil.h"

# define BUFFER_R			8

typedef struct s_tercs	t_tercs;

typedef struct			s_parser
{
	char				*cmd;
	int					id;
	struct s_parser		*next;
}						t_parser;

typedef struct			s_command
{
	char				*line;
}						t_command;

typedef struct			s_letter
{
	char				letter;
	struct s_letter		*next;
	struct s_letter		*prev;
}						t_letter;

struct					s_tercs
{
	int					tty_fd;
	struct termios		term_fd;
	struct termios		term_save;
	size_t				line_len;
};

typedef struct			s_prompt
{
	char				*prompt;
	int					size_prompt;
	int					cursor_l;
}						t_prompt;

typedef struct			s_history
{
	t_letter			*curr;
	struct s_history	*next_h;
	struct s_history	*prev_h;
}						t_history;

typedef struct			s_shell
{
	t_command			*data;
	t_tercs				*tcs;
	t_history			*line_h;
	char				**env;
	t_prompt			*pro;
	t_parser			*el_parser;
}						t_shell;

enum					e_key
{
	RETURN = -1, ASCII = 0, UP = 1, DOWN = 2,
	RIGHT = 3, LEFT = 4
};

/*
** init_shell.c
*/

t_shell			*init_shell(t_shell *root);
char			**init_env(void);
void			get_path(t_parser **el_parser, char **env);

/*
** init_shell2.c
*/

void			show_prompt(t_shell **shell);
void			init_line(t_shell *root);

/*
**	init_types.c
*/

int				set_type(char key[8]);
int				read_key(char key[8], int fd);

/*
** tercs_init.c
*/

void			reset_term(t_shell *root);
int				trcs_putchar(int c);
void			init_trcs(t_tercs *tcs);
int				set_fd(void);

/*
** tercs_control.c
*/

void			tercs_up(t_command **c_line, t_letter **let);
void			tercs_down(t_command **c_line, t_letter **let);
void			tercs_right(t_command **c_line, t_letter **let);
void			tercs_left(t_command **c_line, t_letter **let);
void			tercs_ascii(t_command **c_line, t_letter **let);

/*
** tercs_control2.c
*/

void			tercs_return(t_command **c_line, t_letter **let);

/*
** init_current_list.c
*/

void			char_to_string(t_command **string, t_letter *head);
void			init_ascii(t_letter **head, char key, t_shell **sh);

/*
** error.c
*/

void			error_command(char *s);
int				error_fd(char *s, int fd);

/*
**	lexer_verify.c
*/

void			lex_verify(t_shell **shell, t_letter **let);
void			ft_start_lexer(t_shell **shell, t_letter **list_let);
void			cursor_control(t_letter *list_let);
void			ft_delete_list(t_letter **list_let);
void			cursor_control2(t_letter *list_let);

/*
** init_hist.c
*/

void			init_history(t_letter *current_list, t_history **l_hist);

/*
** debug
*/

void			display_list_test(t_letter *head);
int				ft_list_len(t_letter *head);
void			ft_key_int_type(char key[8], int type);
void			ft_char_to_list(t_letter **ele, t_letter *new_el);
t_letter		*creat_new_element(char let);
void			print_path(char **path);
void			ft_print_hist(t_history *hist_p);

/*
** buil_echo.c
*/

void			buil_echo(int ac, char **msh_av, char **env, char *opt);
char			**buil(int ac, char **av, char **env);
void			ft_element_parser(char **av, t_parser **el_parser);

#endif
