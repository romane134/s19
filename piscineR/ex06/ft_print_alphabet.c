# include <unistd.h>

void ft_putchar(char c);

void ft_print_alphabet(void)
{
  char lettre;
  lettre = 'a';
  while (lettre <= 'z')
  {
    ft_putchar (lettre);
    lettre++;
  }
}
