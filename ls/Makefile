# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/01 13:25:35 by rlucas-d          #+#    #+#              #
#    Updated: 2019/01/07 18:00:40 by rlucas-d         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

C_FLAGS = -Wall -Wextra -Werror -g

OBJ_PATH = ./obj/
LFT_PATH = ./libft/
SRC_PATH = ./src/

OBJ_NAME = $(SRC_NAME:.c=.o)
	INC_NAME = ft_ls.h
	SRC_NAME = ft_stat_right.c ls_test.c

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
INC = -I ./include -I ./libft/includes/

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(LFT_PATH)
	gcc -o $(NAME) -L $(LFT_PATH) -lft $^ -o $@

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	mkdir -p $(OBJ_PATH)
	gcc $(C_FLAGS) $(INC) -o $@ -c $<

clean:
	make -C $(LFT_PATH) clean
	rm -rf $(OBJ_PATH)

fclean: clean
	make -C $(LFT_PATH) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: clean
