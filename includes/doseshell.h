/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doseshell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srabah-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 18:50:06 by srabah-m          #+#    #+#             */
/*   Updated: 2014/03/27 21:55:14 by srabah-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOSESHELL_H
# define DOSESHELL_H

# define A_RED			"\x1b[31m"
# define A_GREEN		"\x1b[32m"
# define A_YELLOW		"\x1b[33m"
# define A_BLUE			"\x1b[34m"
# define A_MAGENTA		"\x1b[35m"
# define A_CYAN			"\x1b[36m"
# define A_RESET		"\x1b[0m"
# define BACKSPACE		127
# define ARROW			27
# define LEFT			68
# define RIGHT			67
# define UP				65
# define DOWN			66
# define CTRLC			3
# define CTRLD			4
# define CTRLL			12
# define TAB			'\t'
# define PIPE			"|"
# define REDI_RIGHT		">"
# define REDI_D_RIGHT	">>"
# define REDI_LEFT		"<"
# define REDI_D_LEFT	"<<"
# define AND			"&&"
# define OR				"||"
# define CMD_SEP		";"
# define BGROUND		"&"
# define TYPE_PIPE		1
# define TYPE_RIGHT		2
# define TYPE_D_RIGHT	3
# define TYPE_LEFT		4
# define TYPE_D_LEFT	5
# define TYPE_AND		6
# define TYPE_OR		7
# define TYPE_CMD_SEP	8
# define TYPE_CMD		9
# define TYPE_ARG		10
# define TYPE_REDI_ARG	11
# define TYPE_BGROUND	12
# include <stdio.h>
# include <unistd.h>
# include <curses.h>
# include <term.h>
# include <termios.h>
# include <fcntl.h>
# include <curses.h>
# include <signal.h>
# include <glob.h>
# include <sys/ioctl.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "ft_strings.h"

typedef struct		s_env
{
	struct s_env	*next;
	struct s_env	*prev;
	char			*var;
	char			*content;
	int				pos;
	int				num;
}					t_env;

typedef struct		s_alias
{
	char			*name;
	char			*cmd;
	struct s_alias	*next;
}					t_alias;

typedef struct		s_shell
{
	int				pipe;
	t_env			*his;
	t_env			*env;
	t_env			*var;
	char			**path;
	char			*pwd;
	char			*old_pwd;
	char			**options;
	char			*home;
	t_alias			*alias;
	int				store_io[2];
}					t_shell;

typedef struct		s_prompt
{
	int				i;
	int				size;
	char			*cmd;
}					t_prompt;

typedef struct		s_char
{
	int				value;
	int				(*fct_ptr)(char buf[3], char **, int *, t_shell *);
}					t_char;

typedef struct		s_win_size
{
	int				cols;
	int				max_cols;
	int				current_cols;
	int				current_line_cols;
}					t_win_size;

typedef struct		s_cmd
{
	char			*word;
	int				type;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}					t_cmd;

typedef struct		s_tree
{
	int				type;
	struct s_param	*param;
}					t_tree;

typedef struct		s_param
{
	struct s_cmd	*cmd;
	struct s_tree	*tree;
	struct s_param	*next;
	struct s_param	*prev;
}					t_param;

typedef struct		s_token
{
	char			*name;
	int				type;
}					t_token;

typedef struct		s_exec
{
	int				type;
	int				(*fct)(t_tree *, t_param *, t_shell *);
}					t_exec;

typedef struct		s_builtin
{
	char			*name;
	int				(*fct_builtin)(t_cmd *, t_shell *);
}					t_builtin;

char		*get_next_line(const int fd);
char		*ft_realloc(char *cmd, int size);
char		*ft_malloc(int size);
void		init_buf(char buf[3]);
void		display_prompt(void);
int			init_term(char **env);
t_shell		*init_shell(char **env, int *tty);
char		**get_path(char **env);
int			backspace_termcaps(char buf[3], char **cmd, int *i, t_shell *shell);
int			add_char(char buf[3], char **cmd, int *i, t_shell *shell);
int			ctrl_termcaps(char buf[3], char **cmd, int *i, t_shell *shell);
int			check_arrow(char buf[3], char **cmd, int *i, t_shell *shell);
void		history_prompt(char buf[3], int *i, char **cmd, t_shell *shell);
t_env		*put_in_list(t_env *root, char *param);
char		*termcaps_prompt(t_shell *shell);
char		*get_cmd_input(t_shell *shell, int tty);
int			exit_raw_mode(void);
int			autocomplete(char buf[3], char **cmd, int *i, t_shell *shell);
int			display_cur_dir(void);
int			display_bin(char *word, t_shell *shell);
int			display_path(char *word);
int			auto_complete(glob_t *pglob);
int			display_glob(glob_t *pglob);
char		*add_some_space(char *command);
t_cmd		*get_cmd_data(char *command);
void		lexing(t_cmd *cmd_data);
int			replace_var(t_cmd *cmd, t_shell *shell);
int			parsing(t_cmd *cmd);
int			check_nbr_cmd(int nb_cmd, int previous, t_cmd **tmp, t_cmd *cmd);
int			check_null_cmd(t_cmd *cmd);
int			check_redi_pipe(t_cmd *cmd);
t_cmd		*verif_redi_pipe(t_cmd *cmd, t_cmd *tmp);
char		*get_home(t_env *env);
char		*get_cd_path(t_cmd *cmd, t_shell *shell);
void		swap_char(char **old_pwd, char **pwd);
int			replace_cmd(t_cmd *tmp, t_env *tmp_his, t_env *his, t_cmd *replace);
int			replace_history(t_cmd *tmp, t_env *his);
int			new_tree(t_cmd **cmd, t_param *param, int *j);
t_tree		*init_cmd_tree(int type);
int			add_param(t_tree *tree, t_cmd *cmd);
t_tree		*get_tree(t_cmd *cmd_data);
t_cmd		*init_cmd_data(void);
t_cmd		*add_to_list(t_cmd *cmd_data, char *word);
int			cut_cmd(t_tree *tree, t_cmd *cmd, int type);
int			exec_tree(t_tree *tree, t_shell *shell);
int			redi_left(char *file, t_shell *shell);
int			redi_d_left(char *key_word, t_shell *shell);
int			write_and_read_redi_d_left(char *buffer);
int			redi_right(char *file, t_shell *shell);
int			redi_d_right(char *file, t_shell *shell);
int			pipe_exec(t_tree *tree, t_param *param, t_shell *shell);
int			and_exec(t_tree *tree, t_param *param, t_shell *shell);
int			or_exec(t_tree *tree, t_param *param, t_shell *shell);
void		del_node(t_cmd *elem);
int			my_alias(t_cmd *cmd, t_shell *shell);
int			my_cd(t_cmd *cmd, t_shell *shell);
int			my_echo(t_cmd *cmd, t_shell *shell);
int			my_env(t_cmd *cmd, t_shell *shell);
int			my_exit(t_cmd *cmd, t_shell *shell);
int			my_history(t_cmd *cmd, t_shell *shell);
int			my_set(t_cmd *cmd, t_shell *shell);
int			my_setenv(t_cmd *cmd, t_shell *shell);
int			my_unalias(t_cmd *cmd, t_shell *shell);
int			my_unset(t_cmd *cmd, t_shell *shell);
int			my_unsetenv(t_cmd *cmd, t_shell *shell);
int			exe_cmd(t_cmd *cmd, t_shell *shell);
int			parsexec(char *cmd, t_shell *shell);
int			back_ground(t_cmd *cmd, t_shell *shell);
t_cmd		*globing(t_cmd *tmp);
char		*globing_for_cd(t_cmd *cmd);
int			globing_for_echo(t_cmd *cmd);
char		*globing_for_setenv(t_cmd *cmd);
int			my_exec(t_cmd *cmd, t_shell *shell);
void		pipe_exit(t_tree *tree, t_param *param);
void		put_alias_off_list(t_alias **alias, t_alias *focus);
int			get_nb_arg(t_cmd *cmd);
int			is_there_a_star(char *word);
int			verif_var(t_cmd	*tmp);
char		**env_in_tab(t_env *env);
char		**cmd_in_tab(t_cmd *cmd);
char		*get_valid_path(char *cmd, t_shell *shell, char **env_tab);
int			ft_get_nb(char *str);
t_env		*already_exist_var(t_cmd *tmp, t_env *var);
int			space_tab_droid(char *str, int i);
int			double_quotes_droid(char *str, t_cmd *cmd, int i);
int			rest_droid(char *str, t_cmd *cmd, int i);
int			quote_droid(char *str, t_cmd *cmd, int i);
int			store_io(t_shell *shell);
t_env		*get_env(char **env);
t_env		*get_root(void);
void		sig_manage(int sig);
void		clean_memory(t_tree *cmd_tree, t_cmd *cmd_data, char *cmd);
int			num_f(t_cmd *tmp, t_env *his);
int			revnum_f(t_cmd *tmp, t_env *his);
int			start_pipe(int pipe_fd[2][2], int *k, t_shell *shell);
int			end_pipe(int pipe_fd[2][2], int *k, t_shell *shell);
int			mid_pipe(int pipe_fd[2][2], int *k, t_shell *shell);

extern int			g_is_a_term;
extern int			g_main_return;
extern t_prompt		g_prompt;
extern int			g_last_exit;

#endif
