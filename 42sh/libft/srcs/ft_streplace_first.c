/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_streplace_first.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 11:53:54 by vjovanov          #+#    #+#             */
/*   Updated: 2019/06/26 19:33:07 by smondesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*create_new_str(char *first, char *second, char *replacement)
{
	char *new_str;
	char *tmp;

	if ((tmp = ft_strjoin(first, replacement)) == NULL)
		return (NULL);
	if ((new_str = ft_strjoin(tmp, second)) == NULL)
	{
		ft_strdel(&tmp);
		return (NULL);
	}
	ft_strdel(&tmp);
	return (new_str);
}

static int		size_first_sub(char *str, char *to_replace)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (ft_strncmp(&str[i], to_replace, ft_strlen(to_replace)) == 0)
			return (i);
		i++;
	}
	return (-1);
}

char			*ft_streplace_first(char *str, char *to_replace,
	char *replacement)
{
	char	*new_str;
	int		size_first;
	char	*first_sub;
	char	*second_sub;

	new_str = NULL;
	first_sub = NULL;
	second_sub = NULL;
	if ((size_first = size_first_sub(str, to_replace)) == -1)
		return (ft_strdup(str));
	if ((first_sub = ft_strndup(str, size_first)) == NULL)
		return (NULL);
	if ((second_sub = ft_strdup(ft_strstr(str, to_replace)
		+ ft_strlen(to_replace))) == NULL)
	{
		ft_strdel(&first_sub);
		return (NULL);
	}
	new_str = create_new_str(first_sub, second_sub, replacement);
	ft_strdel(&first_sub);
	ft_strdel(&second_sub);
	return (new_str == NULL ? NULL : new_str);
}
