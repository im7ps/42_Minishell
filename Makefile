# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/16 21:39:43 by dgioia            #+#    #+#              #
#    Updated: 2023/02/17 15:13:59 by sgerace          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

LIBFT 	= 	libft/libft.a
PRINTF 	= 	ft_printf/libftprintf.a

CC		=	gcc #-Wall -Wextra -Werror

#LINUX
READLINE_LINUX	=	-L/usr/local/lib -I/usr/local/include -lreadline
#MACOS
READLINE_MACOS = -lreadline -L /Users/$(USER)/.brew/opt/readline/lib -I /Users/$(USER)/.brew/opt/readline/include

RM		=	rm -rf

SRC	=	./src/main.c \
		./src/input_checker.c \
		./src/split_variant.c \
		./src/malloc_stuff.c \
		./src/parser.c \
		./src/builtin.c \
		./src/error.c \
		./src/execute.c \
		./src/signals.c \
		./src/constructor.c \
		./src/dollar_exp.c \
		./src/old_split.c \
		./src/utils.c \

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
