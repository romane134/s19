/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 13:51:27 by rlucas-d          #+#    #+#             */
/*   Updated: 2018/10/01 14:01:10 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strdup(char *src)
{
	int		a;
	int		size;
	char	*copy;

	size = 0;
	while (src[size] != '\0')
		size++;
	if (!(copy = (char*)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	a = 0;
	while (a < size)
	{
		copy[a] = src[a];
		a++;
	}
	copy[a] = '\0';
	return (copy);
}
