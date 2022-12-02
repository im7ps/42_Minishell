# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sgerace <sgerace@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/02 19:49:41 by sgerace           #+#    #+#              #
#    Updated: 2022/12/02 20:02:41 by sgerace          ###   ########.fr        #
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

FLAGS = -g #-fsanitize=address #-Wall -Werror -Wextra

#F_IRINA = -lreadline -L/usr/local/opt/readline/lib -I/usr/local/opt/readline/include
FLAG_READLINE = -lreadline -lcurses -L/Users/$(USER)/.brew/opt/readline/lib -I/Users/$(USER)/.brew/opt/readline/include


all: $(NAME)

$(NAME) : $(SRC)
	@$(CC) $(FLAGS) $(FLAG_READLINE) $(SRC) -o $(NAME)

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)
	
re: fclean all

.PHONY: all clean fclean re
