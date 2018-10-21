# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/01 14:19:39 by rlucas-d          #+#    #+#              #
#    Updated: 2018/10/05 02:21:42 by rlucas-d         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC_LIBS = srcs/ft_putchar.c srcs/ft_putstr.c srcs/ft_swap.c srcs/ft_strcmp.c srcs/ft_strlen.c

H_LIBS = includes

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
