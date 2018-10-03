/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 21:38:19 by rlucas-d          #+#    #+#             */
/*   Updated: 2018/10/03 22:09:09 by rlucas-d         ###   ########.fr       */
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
	if (n == 0 || dst == src)
		return (dst);
	while(size < n)
	{
		d[size] = s[size];
		if ((d[size] =(unsigned char)c))
			return (d + size + 1);
		size++;
	}
		return (NULL);
}
