/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 08:56:18 by rlucas-d          #+#    #+#             */
/*   Updated: 2018/10/03 18:05:41 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *s1, const char *s2)
{
	const char	*to_return;
	int			count;

	while (*s1 != '\0')
	{
		count = 0;
		to_return = s1;
		while (*to_return == *(s2 + count) && *(s2 + count) != '\0')
		{
			count++;
			to_return++;
		}
		if (*(s2 + count) == '\0')
		{
			return ((char*)(to_return - count));
		}
		s1++;
	}
	return (0);
}
