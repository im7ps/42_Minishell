# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/16 21:39:43 by dgioia            #+#    #+#              #
#    Updated: 2023/01/23 12:09:35 by sgerace          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

CC		=	gcc -g #-Wall -Wextra -Werror

#LINUX
READLINE_LINUX	=	-L/usr/local/lib -I/usr/local/include -lreadline
#MACOS
READLINE_MACOS = -L/usr/include -lreadline -I$(HOME)/.brew/opt/readline/include

OBJ	=	$(SRC:.c=.o)

LIBFT = libft/libft.a

RM		=	rm -rf

SRC	=	./src/main.c \
		./src/builtin.c \
		./src/error.c \
		./src/lexer.c \

%.o: %.c
			$(CC) ${CFLAGS} -g -c $< -o $@

$(NAME):	$(OBJ)
			@make -C ./libft
			$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(READLINE_MACOS)

all:		$(NAME)

clean:
			@make clean -C libft
			${RM} $(OBJ)

fclean: 	clean
			@make fclean -C libft
			${RM} $(NAME) ${OBJ}

re:			fclean all

.PHONY:		all clean fclean re
