#include "libft.h"

char  *ft_strcpy(char *dest, const char *src)
{
  int a;

  while(src[a] != '\0')
  {
    dest[a] = src[a];
    a++;
  }
  dest[a] = '\0';
  return (dest)
}
