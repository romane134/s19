/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 21:35:30 by rlucas-d          #+#    #+#             */
/*   Updated: 2018/10/03 22:09:12 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

void	*ft_memccpy(void *restrict dst, const void *restrict src, int c,
		size_t n);
int main ()
{
	int a;
	const char src[50] = "coucoucoucoucchievcerbvcejrbcvjer";
	char dest[50];

	a = 's';
	printf("dest ---%s\n", dest);
	printf("ft_memcpy--%s\n", ft_memccpy(dest, src, a, 4));

	printf("memcpy-----%s\n", memccpy(dest, src, a, 4));

	return(0);
}


