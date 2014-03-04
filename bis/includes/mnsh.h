#ifndef MNSH_H
# define MNSH_H

# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <get_next_line.h>
# include <ft_strings.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# define A_RED		"\x1b[31m"
# define A_GREEN	"\x1b[32m"
# define A_YELLOW	"\x1b[33m"
# define A_BLUE		"\x1b[34m"
# define A_MAGENTA	"\x1b[35m"
# define A_CYAN		"\x1b[36m"
# define A_RESET	"\x1b[0m"


typedef struct	s_cmd
{
	char	**my_argv;
	char	cmd_name[256];
	int		fd_in;
	int		fd_out;
	char	out_red[256][256];
	int		is_app[256];
	char	inp_red[256][256];
	int		nb_out;
	int		nb_app;
	int		nb_inp;
}				t_cmd;

typedef struct	s_env
{
	pid_t	pid[256];
	int		new_fd[2];
	int		old_fd[2];
}				t_env;


void	handle_signal(int signo);
void	get_paths(void);
void	attach_path(int id);
void	call_execve(int id);
void	clear_screen(char **av);
void	get_env(void);
char	*get_env_var(char *var);
void	set_env(void);
void	unset_env(void);
int		is_builtin(char *cmd);
void	launch_builtin(char *cmd);
void	my_pwd(void);
void	change_dir(void);
char	*trim_trailing_whitespaces(char *str);
void	ft_fatal(char *error_msg);
char	**ft_split_arg(char *full_cmd);
int		store_redirs(int id, int i);
void	set_redirs(int id);
void	get_redirs(void);
void	close_fd(int i, t_env *e);
void	launch_set_fd(int i, t_env *e);
void	get_my_argv(void);
void	init_cmds(void);
void	get_cmds(char *str);
int		is_builtin_out(void);
void	launch_builtin_out(void);
void	add_tee_cmd(int i);
void	launch_cmds_set(int i, t_env *e);
void	launch_red_end(int i);
void	launch_red_inp(int i);
void	launch_cmd(int i);
void	check_env(void);
void	clear_screen(char **av);
void	handle_signal(int signo);
void	mnsh_2(void);

extern char 	**environ;
extern char		**g_paths;
extern char		**g_full_paths;
extern t_cmd	g_cmd[256];
int				g_nb_cmds;

#endif /* !MNSH_H */
