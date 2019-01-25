/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smondesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 17:04:10 by smondesi          #+#    #+#             */
/*   Updated: 2018/10/15 14:12:42 by smondesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *look, const char *to_find, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (to_find[i] == '\0')
		return ((char*)look);
	while (look[i] && i < len)
	{
		while (look[i + j] == to_find[j] &&
				len > j && look[i + j] && to_find[j])
			j++;
		if (to_find[j] == '\0' && (i + j - 1) < len)
			return ((char*)&look[i]);
		else if (to_find != '\0')
			j = 0;
		i++;
	}
	return (0);
}
