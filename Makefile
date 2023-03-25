# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sgerace <sgerace@student.42roma.it>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/16 21:39:43 by dgioia            #+#    #+#              #
#    Updated: 2023/03/24 23:45:47 by sgerace          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

USER = sgerace

HOME = /Users/${USER}

LIBFT 	= 	libft/libft.a
PRINTF 	= 	ft_printf/libftprintf.a

CC		=	gcc #-Wall -Wextra -Werror

#LINUX
READLINE_LINUX	=	-L/usr/local/lib -I/usr/local/include -lreadline
#MACOS
READLINE_MACOS = -lreadline -L /Users/$(USER)/.brew/opt/readline/lib -I /Users/$(USER)/.brew/opt/readline/include

RM		=	rm -rf

SRC	=	./src/init/main.c \
		./src/parser/input_checker.c \
		./src/utils/split_variant.c \
		./src/utils/malloc_stuff.c \
		./src/parser/parser.c \
		./src/bin/built_in.c \
		./src/bin/ft_echo.c \
		./src/bin/ft_cd.c \
		./src/bin/ft_env.c \
		./src/bin/ft_export.c \
		./src/bin/ft_pwd.c \
		./src/bin/ft_unset.c \
		./src/utils/error.c \
		./src/exec/execute.c \
		./src/signals/signals.c \
		./src/init/constructor.c \
		./src/parser/dollar_exp.c \
		./src/utils/old_split.c \
		./src/exec/exec_cmd.c \
		./src/redirection/ft_redirection.c \
		./src/redirection/redirection_utils.c \
		./src/pipes/ft_pipes.c \
		./src/utils/utils.c \
		./src/gc/garbage.c \
		./src/m_libft/ftm_itoa.c \
		./src/m_libft/ftm_split.c \

OBJ	=	$(SRC:.c=.o)

%.o: %.c
			$(CC) ${CFLAGS} -g -c $< -o $@

$(NAME):	$(OBJ)
			@make -C ./libft
			@make -C ./ft_printf
			$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(PRINTF) $(READLINE_MACOS)

all:		$(NAME)

clean:
			@make clean -C libft
			@make clean -C ft_printf
			${RM} $(OBJ)

fclean: 	clean
			@make fclean -C libft
			@make fclean -C ft_printf
			${RM} $(NAME) ${OBJ}

re:			fclean all

.PHONY:		all clean fclean re
