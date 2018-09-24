int ft_iterative_factorial(int nb)
{
  int res;

  res = nb;
  if (nb == 0)
    res = 1;
  if (nb == 1)
    res = 1;
  if (nb < 0 || nb > 12)
    res = 0;
  while (nb >= 2)
  {
    res = res * (nb - 1);
    nb--;
  }
  return (res);
}

int main(int a)
{
  a = 4;
  ft_iterative_factorial(a);
  return (0);
}
