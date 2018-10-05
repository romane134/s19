/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 11:46:19 by rlucas-d          #+#    #+#             */
/*   Updated: 2018/10/05 03:41:03 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*a;
	char	*b;
	size_t	size;

	size = 0;
	a = (char *)src;
	b = (char *)dst;
	if (a < b)
		while ((int)(len) > 0)
		{
			*(b + len) = *(a + len);
			size--;
		}
	else
		while (size < len)
		{
			*(b + size) = *(a + size);
			size++;
		}
	return (b);
}
