/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 08:56:06 by rlucas-d          #+#    #+#             */
/*   Updated: 2018/10/03 21:13:55 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	size;
	int		a;

	a = 0;
	size = ft_strlen(src);
	while (src[a] != '\0')
	{
		if (n > size)
			dest[a] = '\0';
		else
			dest[a] = src[a];
		a++;
		n--;
	}
	return (dest);
}
