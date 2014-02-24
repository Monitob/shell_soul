shell_soul

Hello, here your gonna find a plan to work the 42sh.

SECTION INIT

Prefix init_ -- file to initialize the terminal.

BUIL-INS -- file to 

Prefix:  buil_

			CD 
			SETENV
			ENV -i
			EXIT
			ECHO
			PWD
			UNSETENV

SIGNAL:
		
		Prefix : sig_

LEXER:
		Prfix : lex_

PARSER:
		Prefix : par_

TERMCAPS :
		Prefix : tercs_

EXECUTION :
		Prefix : exec_

***********************


All the files should have:

prefix_init  --> to initilize the fonction
prefix_clear --> to clean or destroy the fonction
prfix_error  --> to handle the error case

===================================


the main struct:


typedef struct		s_shell
{
	t_command		*data;
	char			**env;
	t_tercs			tcs;
	....
	.....
	....
}					t_shell;

termcaps struct :

typedef struct 		s_tercs
{
	int				tty_fd;
	struct termios	term_fd;
	struct termios	term_save;
	t_stack			*hist;	
	t_line			*line;
	size_t			cursor;
	size_t			line_len;
	...
	...
	..

}					t_tercs



=================================

https://github.com/Monitob/shell_soul.git

==========


