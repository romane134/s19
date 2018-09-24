#include <stdio.h>
#include <string.h>

int ft_strcmp(char *s1, char *s2)
{
  int a;
  int b;

  a = 0;
  b = 0;
  while (s1[a] != '\0' || s2[b] != '\0')
  {
    if (s1[a] != s2[b])
      return (s1[a] - s2[b]);
    a++;
    b++;
  }
  return (0);
}

int main()
{
  char s1[] = "aoucouco";
  char s2[] = "coucouco";

  printf("%d\n", ft_strcmp(s1, s2));
  printf("%d\n", strcmp(s1, s2));
  return (0);
}
