# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/01 16:22:19 by rlucas-d          #+#    #+#              #
#    Updated: 2018/10/05 02:49:55 by rlucas-d         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_display_file

SRC_LIBS = ft_display_file.c

all:
	gcc -Wall -Wextra -Werror -c $(FLAG) $(SRC_LIBS)
	gcc -o $(NAME) ft_display_file.o
clean:
	/bin/rm -f ft_display_file.o

fclean:
	/bin/rm -f ft_display_file.o $(NAME)

re: fclean all
