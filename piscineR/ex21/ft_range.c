#include <stdlib.h>
#include <stdio.h>

int		*ft_range(int min, int max)
{
  int *tab;
  int a;

  if (min >= max)
    return (NULL);
  if (!(tab = (int*)malloc(sizeof(*tab) * ((min - max) + 1))));
    return (NULL);
  a = 0;
  while (min < max)
  {
    tab[a] = min;
    a++;
    min++;
  }
  return (tab);
}
