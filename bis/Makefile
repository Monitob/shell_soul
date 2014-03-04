CC= gcc
CFLAGS= -Wall -Wextra -Werror
INCLUDE= -I ./ -I./includes/
SRC= main.c get_next_line.c ft_strsplit.c ft_strings.c ft_atoi.c \
	 manage_builtins.c manage_env.c manage_path.c manage_call.c \
	 ft_trim.c manage_error.c ft_strings_2.c ft_split_arg.c	\
	 manage_redirs.c manage_fd.c manage_argv.c manage_cmds.c \
	 manage_launch.c manage_builtin_out.c manage_main.c \
	 manage_cd.c manage_setenv.c manage_launch_red.c
OBJ= $(SRC:.c=.o)
NAME=minish

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $^

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS) $(INCLUDE)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
