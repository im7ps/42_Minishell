# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sgerace <sgerace@student.42roma.it>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/02 19:49:41 by sgerace           #+#    #+#              #
#    Updated: 2023/01/13 16:52:03 by sgerace          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC =	./main.c \

OBJC = $(SRC:%.c=%.o)

CC = gcc 

#-Wall -Wextra -Werror

USER = sgerace

#LDFLAGS = -L/opt/homebrew/opt/readline/lib
#CPPFLAGS = -I/opt/homebrew/opt/readline/include

FLAGS = -g -L/usr/local/lib -I/usr/local/include -lreadline #-fsanitize=address #-Wall -Werror -Wextra

#F_IRINA = -lreadline -L/usr/local/opt/readline/lib -I/usr/local/opt/readline/include
FLAG_READLINE = -lreadline -lcurses -L/Users/$(USER)/.brew/opt/readline/lib -I/Users/$(USER)/.brew/opt/readline/include

LIBFT = libft/libft.a

all: $(NAME)

$(NAME) : $(SRC)
	@make -C ./libft
	@$(CC) $(SRC) $(FLAGS) -o $(NAME) $(LIBFT)

clean:
	@make clean -C libft
	@rm -f $(OBJS)

fclean: clean
	@make clean -C libft
	@rm -f $(NAME)
	
re: fclean all

.PHONY: all clean fclean re
