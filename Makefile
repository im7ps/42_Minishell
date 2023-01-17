# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dgioia <dgioia@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/16 21:39:43 by dgioia            #+#    #+#              #
#    Updated: 2023/01/16 22:15:02 by dgioia           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

CC		=	gcc -g #-Wall -Wextra -Werror

#LINUX
FLAGS	=	-L/usr/local/lib -I/usr/local/include -lreadline
#MACOS
FLAG_READLINE = -L/usr/include -lreadline -L$(HOME)/.brew/opt/readline/lib -I$(HOME)/.brew/opt/readline/include

LIBFT = libft/libft.a

SRC	=	src/main.c \
		src/error.c \
		src/builtin.c \

OBJ	=	$(SRC:.c=.o)

RM	=	rm -rf

all: $(NAME)

$(NAME) : $(SRC)
	@make -C ./libft
	@$(CC) $(SRC) -o $(NAME) $(LIBFT) $(FLAG_READLINE)

clean:
	@make clean -C libft
	@rm -f $(OBJS)

fclean: clean
	@make clean -C libft
	@rm -f $(NAME)
	
re: fclean all

.PHONY: all clean fclean re