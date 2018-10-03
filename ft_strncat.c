/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 08:57:57 by rlucas-d          #+#    #+#             */
/*   Updated: 2018/10/03 18:50:16 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>
#include <stdio.h>

char	*ft_strncat(char *dest, const char *src, size_t n)
{
	size_t	a;
	size_t	b;

	a = 0;
	b = 0;
	while (dest[a] != '\0')
		a++;
	while (b < n)
	{
		dest[a + b] = src[b];
		b++;
	}
	if (src[n] != '\0')
		dest[a + b] = '\0';
	return (dest);
}

int		main(void)
{
	char a[] = "aaaaa";
	char b[90] = "bcdefg";
	char c[90] = "aaaaa";
	char d[90] = "bcdefg";

	printf("%s\n", ft_strncat(a, b, 4));
	printf("%s\n", strncat(c, d, 4));
	return (0);
}
