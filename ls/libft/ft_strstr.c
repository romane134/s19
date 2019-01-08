/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smondesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 17:00:46 by smondesi          #+#    #+#             */
/*   Updated: 2018/10/18 11:26:15 by smondesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *look, const char *to_find)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (to_find[i] == '\0')
		return ((char*)look);
	while (look[i])
	{
		while (look[i + j] == to_find[j] && look[i + j])
			j++;
		if (to_find[j] == '\0')
			return ((char*)&look[i]);
		else if (to_find[j] != '\0')
			j = 0;
		i++;
	}
	return (0);
}
