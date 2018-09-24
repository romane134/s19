#include <stdio.h>

int ft_recursive_factorial(int nb)
{
  if (nb == 0)
    return(1);
  if (nb == 1)
    return (1);
  if (nb < 0 || nb > 12)
    return (0);
  if (nb >= 2)
    {
      return (nb * ft_recursive_factorial(nb - 1));
    }
    printf("%d\n" );
    return (0);
}

int main(int a)
{
  a = 4;
  ft_recursive_factorial(a);
  return (0);
}
