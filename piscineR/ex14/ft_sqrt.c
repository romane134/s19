#include <stdio.h>
int ft_sqrt(int nb)
{
  int a;

  a = 1;
  while (nb > (a * a) || nb < 0)
    a++;
  if (nb == (a * a))
    return (a);
  else
    return (0);
}

int main (int a)
{
  a = 8;
  printf("%d\n", ft_sqrt(a));
  return (0);
}
