/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 14:30:59 by rlucas-d          #+#    #+#             */
/*   Updated: 2018/10/04 19:05:50 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const char *a;
	const char *b;

	a = (const char *)s1;
	b = (const char *)s2;
	while (n > 0)
	{
		if (*a != *b)
			return (*a - *b);
		else
		{
			n--;
			a++;
			b++;
		}
	}
	return (0);
}
