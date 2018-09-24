#include <unistd.h>

void ft_putchar (char c)
{
  write (1, &c, 1);
}

void ft_putstr(char *str)
{
  int a;

  a = 0;
  while (str[a] != '\0')
    {
      ft_putchar(str[a]);
      a++;
    }
}
int main(int argc, char **argv)
{
  int a;

  a = 1;
  while (a < argc)
  {
    ft_putstr(argv[a]);
    ft_putchar('\n');
    a++;
  }
  return (0);
}
