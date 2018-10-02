#include "libft.h"

char    *ft_strcat(char *dest, const char *src)
{
  int a;
  int b;

  a = 0;
  b = 0;
  while(dest[a] != '\0')
    a++;
  while (src[b] != '\0')
  {
    dest[a + b] = src[b];
    b++;
  }
  dest[a + b] = '\0';
  return (dest);
}
