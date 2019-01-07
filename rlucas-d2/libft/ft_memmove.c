/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smondesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 11:07:30 by smondesi          #+#    #+#             */
/*   Updated: 2018/10/15 15:15:27 by smondesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*s;
	unsigned char	*d;
	size_t			i;

	i = 0;
	s = (unsigned char *)src;
	d = (unsigned char *)dst;
	if (s == d)
		return (dst);
	if (s < d)
	{
		while (len--)
		{
			d[len] = s[len];
		}
	}
	else
		while (i < len)
		{
			d[i] = s[i];
			i++;
		}
	return (dst);
}
