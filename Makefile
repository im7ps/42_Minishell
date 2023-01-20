# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sgerace <sgerace@student.42roma.it>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/16 21:39:43 by dgioia            #+#    #+#              #
#    Updated: 2023/01/20 17:35:50 by sgerace          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

CC		=	gcc -g #-Wall -Wextra -Werror

#LINUX
READLINE_LINUX	=	-L/usr/local/lib -I/usr/local/include -lreadline
#MACOS
READLINE_MACOS = -L/usr/include -lreadline -I$(HOME)/.brew/opt/readline/include

LIBFT = libft/libft.a

SRC	=	src/main.c \
		src/error.c \
		src/builtin.c \
		src/lexer.c \

OBJ	=	$(SRC:.c=.o)

RM	=	rm -rf

all: $(NAME)

$(NAME) : $(SRC)
	@make -C ./libft
	@$(CC) $(SRC) -o $(NAME) $(READLINE_LINUX)  $(LIBFT)

clean:
	@make clean -C libft
	@rm -f $(OBJS)

fclean: clean
	@make clean -C libft
	@rm -f $(NAME)
	
re: fclean all

.PHONY: all clean fclean re