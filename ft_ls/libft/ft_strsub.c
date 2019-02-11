/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smondesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 18:11:55 by smondesi          #+#    #+#             */
/*   Updated: 2019/02/10 16:39:13 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*c;
	size_t	i;

	i = 0;
	if (s != NULL)
	{
		c = (char*)malloc(sizeof(char) * (len + 1));
		if (c == NULL)
			return (0);
		while (i < len)
		{
			c[i] = s[start];
			i++;
			start++;
		}
		c[i] = '\0';
		return (c);
	}
	return (0);
}
