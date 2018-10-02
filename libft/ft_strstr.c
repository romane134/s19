#include "libft.h"

char	*ft_strstr(const char *s1, const char *s2)
{
  char	*to_return;
	int		count;

	while (*str != '\0')
	{
		count = 0;
		to_return = str;
		while (*to_return == *(to_find + count) && *(to_find + count) != '\0')
		{
			count++;
			to_return++;
		}
		if (*(to_find + count) == '\0')
		{
			return (to_return - count);
		}
		str++;
	}
	return (0);
}
