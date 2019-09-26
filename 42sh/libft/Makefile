# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bjovanov <bjovanov@student.19.be>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/03 21:55:10 by bjovanov          #+#    #+#              #
#    Updated: 2018/10/31 18:18:02 by bjovanov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC_DIR = ./srcs
INC_DIR = ./includes
OBJ_DIR = ./obj

SRC_FILES =	ft_atoi.c ft_bzero.c ft_error.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
			ft_isdigit.c ft_islower.c ft_isprint.c ft_isspace.c ft_isupper.c ft_itoa.c \
			ft_lstadd.c ft_lstdel.c ft_lstdelone.c ft_lstiter.c ft_lstmap.c ft_lstnew.c \
			ft_memalloc.c ft_memccpy.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memdel.c ft_memmove.c \
			ft_memset.c ft_putchar.c ft_putchar_fd.c ft_putendl.c ft_putendl_fd.c ft_putnbr.c \
			ft_putnbr_fd.c ft_putstr.c ft_putstr_fd.c ft_strcat.c ft_strchr.c ft_strclr.c ft_strcmp.c \
			ft_strcpy.c ft_strdel.c ft_strdup.c ft_strequ.c ft_striter.c ft_striteri.c ft_strjoin.c \
			ft_strlcat.c ft_strlen.c ft_strmap.c ft_strmapi.c ft_strncat.c ft_strncmp.c ft_strncpy.c \
			ft_strndup.c ft_strnequ.c ft_strnew.c ft_strnstr.c ft_strrchr.c ft_strsplit.c ft_strstr.c \
			ft_strsub.c ft_strtrim.c ft_tolower.c ft_toupper.c ft_strclen.c ft_strstrsplit.c \
			ft_strreplace.c ft_array_length.c ft_sqrt.c ft_dtoa/ft_dtoa.c ft_dtoa/ft_dtoa_ext.c \
			ft_ldtoa/ft_ldtoa.c ft_ldtoa/ft_ldtoa_ext.c ft_atoll.c ft_atoull.c ft_initarray.c \
			ft_ctoa.c ft_intset.c ft_itoa_base.c ft_lltoa.c ft_lltoa_base.c ft_ltoa.c \
			ft_ltoa_base.c ft_stoa.c ft_strdupwc.c ft_uctoa.c ft_uitoa.c ft_uitoa_base.c \
			ft_ulltoa.c ft_ulltoa_base.c ft_ultoa.c ft_ultoa_base.c ft_ustoa.c \
			ft_strremove.c ft_strtoupper.c ft_countchr.c get_next_line.c ft_str3join.c ft_strdupwstr.c \
			ft_strsplit_space.c ft_strjoin_free.c ft_2dtabdel.c ft_streplace_first.c

PRINTF_FILES = srcs/ft_printf.c srcs/fill_data.c srcs/data.c srcs/config_checker.c srcs/config.c \
				srcs/sub_checker.c srcs/dispatcher.c srcs/set_type.c srcs/formatting.c

PRINTF_FILES += srcs/convert/convert_char.c srcs/convert/convert_double.c srcs/convert/convert_hexa.c \
				srcs/convert/convert_int.c srcs/convert/convert_hexa_upper.c srcs/convert/convert_octal.c \
				srcs/convert/convert_pointer.c srcs/convert/convert_string.c \
				srcs/convert/convert_unsigned.c srcs/convert/convert_percent.c \
				srcs/convert/convert_binary.c

PRINTF_FILES += srcs/flags/flags.c srcs/flags/generic_flags.c srcs/flags/min_field_width.c srcs/flags/octal_flags.c \
			 	srcs/flags/hexa_flags.c srcs/flags/binary_flags.c srcs/flags/binary_flags_ext.c

SRC_FILES += $(addprefix ft_printf/, $(PRINTF_FILES))

SRC = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ = $(addprefix $(OBJ_DIR)/, $(subst .c,.o, $(SRC_FILES)))

CC = gcc
CFLAGS = -Wall -Wextra -Werror

.PHONY: all clean fclean re

all:
	@mkdir -p $(OBJ_DIR)
	@make $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@echo "Creation de la librairie $(NAME)..."
	@ranlib $(NAME)
	@echo "Indexation de la librairie $(NAME)..."

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "Compilation du fichier "$(KGRN) $(subst .c,,$<)$(KNRM)
	@mkdir -p $(dir $@) && $(CC) $(CFLAGS) -I$(INC_DIR) -o $@ -c $<

clean:
	@rm -rf $(OBJ_DIR)
	@echo "Suppression des fichiers objets..."

fclean: clean
	@rm -rf $(NAME)
	@echo "Suppression du fichier $(NAME)..."

re: fclean all
