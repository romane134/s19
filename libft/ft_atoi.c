#include "libft.h"

int   atoi(const char *str)
{
  int result;
  int a;
  int neg;

  a = 0;
  result = 0;
  neg = 1;
  while (str[a] == ' ' || str[a] == '\t' || str[a] == '\n' || str[a] == '\r'
  || str[a] == '\f' || str[a] == '\v')
  		a++;
  if (str[a] == '-')
  {
  	neg = -1;
  	a++;
  }
  if (str[a] == '+')
  	a++;
  while (str[a] >= 48 && str[a] <= 57)
  {
  	result = result * 10 + str[a] - '0';
  	a++;
  }
  return (result * neg);
}
