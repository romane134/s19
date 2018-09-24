#include <stdio.h>
int ft_strlen(char *str)
{
  int a;
  while (str[a] != '\0')
    a++;
  return (a);
}

int main ()
{
  char c[] = "salut les loustiques";
  printf("%d\n", ft_strlen(c));
  return (0);
}
