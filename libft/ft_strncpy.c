#include "libft.h"

char  *ft_strncpy(char *dest, const char *src, size_t n)
{
  int size;
  size_t a;

  a = 0;
  size = ft_strlen(src);
  while (a < n)
  {
    if (n < size)
      dest[a] = src[a];
    else
      src[a] = '\0'
    a++;
  }
  return (dest);
}
