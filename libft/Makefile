# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sgerace <sgerace@student.42roma.it>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/26 15:43:03 by sgerace           #+#    #+#              #
#    Updated: 2023/03/08 23:59:40 by sgerace          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS		=	ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c\
  				ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c\
				ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c\
				ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c\
				ft_split.c ft_strchr.c ft_strrchr.c ft_strdup.c\
  				ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c\
				ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c\
				ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c\
				ft_lstlast.c ft_lstadd_back.c ft_strndup.c ft_substr_old.c \

OBJS		= ${SRCS:.c=.o}

CC			= gcc -g

RM			= rm -f

CFLAGS		= -Wall -Wextra -Werror

all:		${NAME}

$(NAME):	${OBJS}
			ar rc ${NAME} ${OBJS}

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean ${NAME}
