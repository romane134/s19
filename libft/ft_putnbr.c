#include "libft.h"

void ft_putnbr(int n)
{
  long lnb;

	lnb = nb;
	if (lnb < 0)
	{
		lnb = -lnb;
		ft_putchar('-');
	}
	if (lnb > 9)
	{
		ft_putnbr(lnb / 10);
	}
	ft_putchar((lnb % 10) + 48);
}
