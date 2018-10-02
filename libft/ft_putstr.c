#include "libft.h"

void ft_putstr(char *str)
{
  int a;
  while (str[a] != '\0')
  {
    ft_putchar(str[a]);
    a++;
  }
}
