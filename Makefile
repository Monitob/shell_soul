# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbernabe <jbernabe@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/02/04 22:30:52 by jbernabe          #+#    #+#              #
#    Updated: 2014/03/02 12:35:27 by jbernabe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

NAME = 42sh 

CFLAGS = -g --debug -Wall -Wextra -Werror

PATH_SRC = ./src
PATH_OBJ = ./objs
PATH_INC = ./includes
LFLAGS = -ltermcap

SRC = init_shell.c init_shell2.c tercs_init.c init_types.c \
	  tercs_control.c init_current_list.c \
	  error.c fct_debug.c

OBJ = $(patsubst %.c, $(PATH_OBJ)/%.o, $(SRC))

all:  lib $(NAME)

lib:
		@make -C libft 

$(NAME): $(OBJ)
		@$(MAKE) -C libft
		@$(CC) $(CFLAGS) $(LFLAGS) -o $(NAME) $(OBJ) -L./libft/  \
		-L/usr/lib/ -ltermcap -lft

$(PATH_OBJ)/%.o: $(addprefix $(PATH_SRC)/, %.c)
	@mkdir -p $(PATH_OBJ)
	@$(CC) $(CFLAGS) -o $@ -I $(PATH_INC) -Ilibft -c $<
	@echo Compiling object : $<

clean:
#	@$(MAKE) -C libft $@
	@rm -f $(OBJ) 

fclean:	clean
#	@$(MAKE) -C libft $@
	@rm -f $(OBJ)
	@rm -f $(NAME)

re: clean fclean all 

.PHONY: re, clean, fclean 
