# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/05 10:18:21 by rlucas-d          #+#    #+#              #
#    Updated: 2019/01/08 12:14:45 by rlucas-d         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: fclean all
NAME	= fdf

# src / obj files
SRC		= fdf.c ft_color.c ft_draw.c ft_edit_point_iso.c ft_mlx.c \
		  ft_read_fdf.c selection_square.c ft_strsplit_v2.c palette.c \
		  ../GNL/get_next_line.c draw_2.c ft_mlx_mouse.c ft_edit_point_para.c \
		  ft_title.c

OBJ		= $(addprefix $(OBJDIR),$(SRC:.c=.o))

# compiler
CC		= gcc
CFLAGS	= #-Wall -Wextra -Werror
# mlx library
MLX		= ./miniLibX/
MLX_LIB	= $(addprefix $(MLX),mlx.a)
MLX_INC	= -I ./miniLibX
MLX_LNK	= -L ./miniLibX -l mlx -framework OpenGL -framework AppKit

# ft library
FT		= ./libft/
FT_LIB	= $(addprefix $(FT),libft.a)
FT_INC	= -I ./libft
FT_LNK	= -L ./libft -l ft

# directories
SRCDIR	= ./src/
INCDIR	= ./includes/
OBJDIR	= ./obj/

all: obj $(FT_LIB) $(MLX_LIB) $(NAME)

obj:
	@mkdir -p $(OBJDIR)

$(OBJDIR)%.o:$(SRCDIR)%.c
	@$(CC) $(MLX_INC) $(FT_INC)  -I $(INCDIR) -o $@ -c $(CFLAGS) $<
	@echo "compilation de $< en $@"

$(FT_LIB):
	@make -C $(FT)

$(MLX_LIB):
	@make -C $(MLX)

$(NAME): $(OBJ)
	@$(CC) $(OBJ) -fsanitize=address $(MLX_LNK) $(FT_LNK) -lm -o $(NAME)

clean:
	@rm -rf $(OBJDIR)
	@make -C $(FT) clean
	@make -C $(MLX) clean

fclean: clean
	@rm -rf $(NAME)
	@make -C $(FT) fclean

re: fclean all
