#ifndef LIBFT_H
# define LIBFT_H

#include <unistd.h>
#include <stdlib.h>
#include <string.h>


void ft_putstr(char *str);
void ft_putchar(char c);
void ft_putnbr(int n);

size_t  ft_strlen(const char *s);
char  *ft_strcpy(char *dest, const char *src);
char  *ft_strncpy(char *dest, const char *src, size_t n);
//char	*ft_strstr(const char *s1, const char *s2);
//char  *ft_strdup(const char *s);
void ft_strclr(char *s);
//char  *ft_strnew(size_t size);
char    *ft_strcat(char *dest, const char *src);
char   *ft_strncat(char *dest, const char *src, size_t n);

int   ft_atoi(/*const*/ char *str);

#endif
