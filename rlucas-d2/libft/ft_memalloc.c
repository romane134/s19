/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smondesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 17:57:09 by smondesi          #+#    #+#             */
/*   Updated: 2018/10/15 10:46:06 by smondesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	unsigned char	*c;
	size_t			i;

	i = 0;
	c = (unsigned char *)malloc(sizeof(char) * (size));
	if (c == NULL)
		return (NULL);
	if (c)
	{
		while (size--)
		{
			c[i] = '\0';
			i++;
		}
	}
	return ((void *)c);
}
