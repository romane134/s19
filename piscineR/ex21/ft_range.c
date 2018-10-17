/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 14:02:08 by rlucas-d          #+#    #+#             */
/*   Updated: 2018/10/01 18:19:48 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int		*ft_range(int min, int max)
{
	int *tab;
	int a;
	int size;

	size = max - min;
	a = 0;
	if (min >= max)
		return (0);
	tab = (int*)malloc(sizeof(*tab) * (size + 1));
	while (a < size)
	{
		tab[a] = min;
		a++;
		min++;
	}
	return (tab);
}
