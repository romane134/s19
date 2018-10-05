# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/05 01:36:09 by rlucas-d          #+#    #+#              #
#    Updated: 2018/10/05 03:02:26 by rlucas-d         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC_LIB = ft_isprint.c ft_memset.c ft_strcat.c ft_strlcat.c ft_strsplit.c \
ft_itoa.c ft_putchar.c ft_strchr.c ft_strlen.c ft_strstr.c  ft_strrchr.c\
auteur ft_memalloc.c ft_putchar_fd.c ft_strclr.c ft_strncat.c ft_strsub.c \
ft_atoi.c ft_memccpy.c ft_putendl.c ft_strcmp.c ft_strncmp.c ft_strtrim.c \
ft_bzero.c ft_memchr.c ft_putendl_fd.c ft_strcpy.c ft_strncpy.c \
ft_tolower.c ft_isalnum.c ft_memcmp.c ft_putnbr.c ft_strdel.c ft_strnequ.c \
ft_toupper.c ft_isalpha.c ft_memcpy.c ft_putnbr_fd.c ft_strdup.c ft_strnew.c \
ft_isascii.c ft_memdel.c ft_putstr.c ft_strequ.c ft_strnstr.c ft_isdigit.c \
ft_memmove.c ft_putstr_fd.c ft_strjoin.c 

H_LIB = inlude/

FLAG = -Wall -Wextra -Werror

all:
	gcc $(FLAG) -c $(SRC_LIBS) -I $(H_LIBS)
	ar rc $(NAME) *.o
	ranlib $(NAME)

clean:
	rm -rf *.o

fclean:
	rm -rf $(NAME)

re: fclean all
