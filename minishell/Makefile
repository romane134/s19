# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/11 14:25:35 by rlucas-d          #+#    #+#              #
#    Updated: 2019/02/12 18:46:30 by rlucas-d         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: fclean all
NAME	= minishell

SRC		= minishell.c msh_message.c
OBJ		= $(addprefix $(OBJDIR),$(SRC:.c=.o))

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror

FT		= ./libft/
FT_LIB	= $(addprefix $(FT),libft.a)
FT_INC	= -I ./libft
FT_LNK	= -L ./libft -l ft


SRCDIR	= ./src/
INCDIR	= ./includes/
OBJDIR	= ./obj/

all: obj $(FT_LIB) $(NAME)

obj:
		@mkdir -p $(OBJDIR)

$(OBJDIR)%.o:$(SRCDIR)%.c
		@$(CC)  $(FT_INC)  -I $(INCDIR) -o $@ -c $(CFLAGS) $<
		@echo "compilation de $< en $@"

$(FT_LIB):
		@make -C $(FT)

$(NAME): $(OBJ)
		@$(CC) $(OBJ)  $(FT_LNK) -lm -o $(NAME) #-fsanitize=address
clean:
		@rm -rf $(OBJDIR)
		@make -C $(FT) clean

fclean: clean
		@rm -rf $(NAME)
		@make -C $(FT) fclean

re: fclean all
