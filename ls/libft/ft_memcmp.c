/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smondesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 17:35:19 by smondesi          #+#    #+#             */
/*   Updated: 2018/10/12 14:06:08 by smondesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	char		*z1;
	char		*z2;
	size_t		i;

	i = 0;
	z1 = (char *)s1;
	z2 = (char *)s2;
	while (n > i)
	{
		if (z1[i] != z2[i])
			return ((unsigned char)z1[i] - (unsigned char)z2[i]);
		i++;
	}
	return (0);
}
