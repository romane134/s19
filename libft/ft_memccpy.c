/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 21:38:19 by rlucas-d          #+#    #+#             */
/*   Updated: 2018/10/05 09:18:32 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *restrict dst, const void *restrict src, int c,
		size_t n)
{
	char	*d;
	char	*s;
	size_t	size;

	size = 0;
	d = (char*)dst;
	s = (char*)src;
	while (size < n)
	{
		d[size] = s[size];
		if (d[size] == (unsigned char)c)
		{
			size++;
			return (d + sizeof(char) * size);
		}
		size++;
	}
	return (NULL);
}
