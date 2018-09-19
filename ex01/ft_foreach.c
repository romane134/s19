
#include <stdio.h>

void	ft_foreach(int *tab, int length, void(*f)(int));

void	ft_log(int nb)
{
	printf("%i\n", nb);
}

void ft_foreach(int *tab, int length, void(*f)(int))
{
  int a;
  a = 0;
  while (a < length)
  {
    f(tab[a]);
    a++;
  }

}
int		main(void)
{
	int		tab[9];
	int		i;

	i = 0;
	while (i < 9)
		{
      tab[i] = i;
      i++;
    }

	ft_foreach(tab, 9, &ft_log);
	return (0);
}
