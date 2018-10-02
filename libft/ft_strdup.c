#include "libft.h"

char  *ft_strdup(const char *s)
{
  char *copy;
  size_t size;

  size = strlen(s)
  if (!(copy =(char *)malloc(sizeof(char) * (size /*ft_strlen(s)*/)+ 1))))
    return (NULL);
      ft_strcpy(copy, s); //mettre variable en plus?
      return (copy);
}
