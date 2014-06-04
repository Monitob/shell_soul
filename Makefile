# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbernabe <jbernabe@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/02/04 22:30:52 by jbernabe          #+#    #+#              #
#    Updated: 2014/03/27 22:40:42 by jbernabe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

NAME = 42sh

CFLAGS = -Wall -Wextra -Werror

PATH_SRC = ./src
PATH_OBJ = ./objs
PATH_INC = ./includes
LFLAGS = -lncurses

SRC=add_space.c \
	autocomplete.c \
	autocomplete_2.c \
	bg.c \
	check.c \
	display.c \
	display_glob.c \
	exec_cmd.c \
	exec_tree.c \
	ft_alias.c \
	ft_atoi.c \
	ft_cd.c \
	ft_echo.c \
	ft_env.c \
	ft_errors.c \
	ft_exec.c \
	ft_exit.c \
	ft_history.c \
	ft_set.c \
	ft_setenv.c \
	ft_strings.c \
	ft_strings_2.c \
	ft_strings_3.c \
	ft_strings_4.c \
	ft_strings_5.c \
	ft_strsplit.c \
	ft_unalias.c \
	ft_unset.c \
	ft_unsetenv.c \
	ft_utils.c \
	ft_utils_2.c \
	ft_utils_3.c \
	get_cd.c \
	get_cmd_data.c \
	get_cmd_data_2.c \
	get_cmd_input.c \
	get_next_line.c \
	get_path.c \
	glob.c \
	history.c \
	init.c \
	init_2.c \
	lexing.c \
	list_utils.c \
	main.c \
	main_2.c \
	manage_pipes.c \
	manage_redir.c \
	parse_tree.c \
	parsing.c \
	pipe_execs.c \
	redi_pipe.c \
	rep_history.c \
	rep_history_2.c \
	replace.c \
	termcaps.c \
	termcaps_manage.c \
	tree_utils.c \

OBJ = $(patsubst %.c, $(PATH_OBJ)/%.o, $(SRC))

all:  lib $(NAME)

lib:
		@make -C libft

$(NAME): $(OBJ)
		@$(MAKE) -C libft
		@$(CC) $(CFLAGS) $(LFLAGS) -o $(NAME) $(OBJ) -L./libft/  \
		-L/usr/lib/ -ltermcap -lft -lncurses

$(PATH_OBJ)/%.o: $(addprefix $(PATH_SRC)/, %.c)
	@mkdir -p $(PATH_OBJ)
	@$(CC) $(CFLAGS) -o $@ -I $(PATH_INC) -Ilibft -c $<
	@echo Compiling object : $<

clean:
	@$(MAKE) -C libft $@
	@rm -f $(OBJ)

fclean:	clean
	@$(MAKE) -C libft $@
	@rm -f $(OBJ)
	@rm -f $(NAME)

re: fclean all

.PHONY: re, clean, fclean
