#include <stdlib.h>
#include <stdio.h>

char *ft_strdup(char *src)
{
  int a;
  int size;
  char *tab;

  size = 0;
  while (src[size] != '\0')
    size++;
  if (size == 0)
  		return (NULL);
  else
    tab = (char*)malloc(sizeof(char) * (size + 1));
  a = 0;
  while (a < size)
  {
    tab[a] = src[a];
    a++;
  }
  tab[a] = '\0';    //si ne le met pas, affiche un carractere en plus
  printf("%s\n", tab);
  return (tab);
}

int main()
{
  char str[90] = "coucou";
  ft_strdup(str);
  return (0);
}
