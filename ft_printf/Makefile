# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sgerace <sgerace@student.42roma.it>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/12 21:33:03 by sgerace           #+#    #+#              #
#    Updated: 2022/05/23 16:03:58 by sgerace          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 		libftprintf.a

SRCS = 	ft_printf_main.c \
		ft_printf_string_utils.c \
		ft_printf_num_utils.c

OBJS		=	${SRCS:.c=.o}

CC			= gcc

RM			= rm -f

CFLAGS		= -g -Wall -Wextra -Werror

all:		${NAME}

$(NAME):	${OBJS}
			ar -rcs ${NAME} ${OBJS}

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean ${NAME}