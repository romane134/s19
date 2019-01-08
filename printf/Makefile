# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/05 11:22:47 by rlucas-d          #+#    #+#              #
#    Updated: 2018/11/05 11:34:46 by rlucas-d         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
INCLUDES = -I ./includes/
SRC_LIB = src/ft_printf.c

OBJ = $(SRC_LIB:%.c=%.o)

FLAG = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo "Compilation de la lib"

%.o: %.c
	@gcc -o $@ -c $(FLAGS) $< $(INCLUDES)
	@echo "Compilation de $< en $@"

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all
