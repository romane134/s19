#include "libft.h"

size_t  ft_strlen(const char *s)
{
  size_t a;

  while (s[a] != '\0')
    a++;
  return(a);
}
