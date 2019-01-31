# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smondesi <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/03 13:45:09 by smondesi          #+#    #+#              #
#    Updated: 2019/01/28 11:58:42 by smondesi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = ft_atoi.c ft_memcpy.c ft_putnbr_fd.c ft_strdup.c \
	ft_strnew.c ft_bzero.c ft_putstr.c ft_strequ.c\
	ft_strnstr.c ft_isalnum.c ft_memset.c ft_putstr_fd.c\
	ft_strjoin.c ft_strrchr.c ft_isalpha.c ft_print_tab.c\
	ft_strcat.c ft_strsplit.c ft_isascii.c ft_putchar.c\
	ft_strchr.c ft_memdel.c ft_memmove.c ft_memchr.c\
	ft_strlen.c ft_strsub.c ft_isdigit.c ft_putchar_fd.c\
	ft_strclr.c ft_strncat.c ft_strstr.c ft_isprint.c\
	ft_putendl.c ft_strcmp.c ft_strncmp.c ft_strtrim.c\
	ft_itoa.c ft_putendl_fd.c ft_strcpy.c ft_strncpy.c\
	ft_tolower.c ft_memccpy.c ft_putnbr.c ft_strdel.c\
	ft_strnequ.c ft_toupper.c ft_striter.c ft_striteri.c\
	ft_strmap.c ft_strmapi.c ft_memcmp.c ft_memalloc.c\
	ft_strlcat.c ft_lstnew.c ft_lstadd.c ft_lstdelone.c ft_swap.c ft_strrev.c\
	ft_lstdel.c ft_lstiter.c ft_lstmap.c st_itoa_base.c ft_count_words.c\
	ft_abs.c ft_free_tab.c get_next_line.c mini_printf.c\
	ft_ismaj.c
OBJ = $(SRC:%.c=%.o)

all: $(NAME)

$(NAME):
	@gcc -c -I. -Wall -Wextra -Werror $(SRC)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

clean:
	@/bin/rm -rf $(OBJ)

fclean: clean
	@/bin/rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean re all
