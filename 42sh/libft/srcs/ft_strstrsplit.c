/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstrsplit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjovanov <bjovanov@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 18:22:04 by bjovanov          #+#    #+#             */
/*   Updated: 2019/06/05 17:52:59 by smondesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		remove_array(char **array, int index)
{
	while (index >= 0)
	{
		free(array[index]);
		index--;
	}
	free(array);
}

static int		count_words(const char *haystack, const char *needle)
{
	int			count;
	const char	*str;
	size_t		hay_len;
	size_t		needle_len;

	count = 0;
	str = haystack;
	hay_len = ft_strlen(haystack);
	needle_len = ft_strlen(needle);
	while ((str = ft_strstr(str, needle)) != NULL)
	{
		str += needle_len;
		count++;
	}
	if (ft_strcmp(haystack + (hay_len - needle_len), needle) != 0)
		count++;
	if (ft_strncmp(haystack, needle, needle_len) == 0)
		count--;
	return (count);
}

static char		*create_word(const char *haystack, const char *needle)
{
	size_t	len;
	size_t	hay_len;
	char	*str;
	char	*word;

	hay_len = ft_strlen(haystack);
	str = ft_strstr(haystack, needle);
	len = (str == NULL ? hay_len : hay_len - ft_strlen(str));
	if ((word = ft_strsub(haystack, 0, len)) == NULL)
		return (NULL);
	return (word);
}

static void		create_array(const char *haystack, const char *needle,
		char **str)
{
	int		i;
	size_t	needle_len;

	i = 0;
	needle_len = ft_strlen(needle);
	if (ft_strncmp(haystack, needle, needle_len) != 0)
	{
		if ((str[i] = create_word(haystack, needle)) == NULL)
			return (remove_array(str, i));
		i++;
	}
	while ((haystack = ft_strstr(haystack, needle)) != NULL)
	{
		haystack += needle_len;
		if (ft_strcmp(haystack - needle_len, needle) == 0)
			continue;
		if ((str[i] = create_word(haystack, needle)) == NULL)
			return (remove_array(str, i));
		i++;
	}
	str[i] = 0;
}

char			**ft_strstrsplit(const char *haystack, const char *needle)
{
	char **str;

	if (haystack == NULL || needle == NULL)
		return (NULL);
	str = (char**)malloc(sizeof(char*) * (count_words(haystack, needle) + 1));
	if (str == NULL)
		return (NULL);
	create_array(haystack, needle, str);
	return (str);
}
