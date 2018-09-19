NAME = libft.a
SRC_LIBS = srcs/ft_putchar.c srcs/ft_putstr.c srcs/ft_swap.c srcs/ft_strcmp.c srcs/ft_strlen.c
H_LIBS = includes
FLAG = -Wall -Wextra -Werror

all:
  gcc &(FLAG) -c &(SRC_LIBS) -I&(H_LIBS)
  ar rc &(NAME) *.o
  ranlib &(NAME)
clean:
  rm -rf *.o
fclean: clean
  rm -rf &(NAME)
re: fclean all
