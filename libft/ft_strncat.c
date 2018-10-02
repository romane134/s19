#include "libft.h"
#include <string.h>
#include <stdio.h>

char   *ft_strncat(char *dest, const char *src, size_t n)
{
  int a;
  int b;

  a = 0;
  b = 0;
  while(dest[a] != '\0')
    a++;
  while (b < n)
  {
    dest[a + b] = src[b];
    b++;
  }
  if (src[n] != '\0')
      dest[a + b] ='\0';
  return (dest);
}

int main()
{
  char a[90] = "aaaaa";
  char b[90] = "bcdefg";
  char c[90] = "aaaaa";
  char d[90] = "bcdefg";
  printf("%s\n", ft_strncat(a, b, 4));
  printf("%s\n", strncat(c, d, 4));
  return (0);
}
