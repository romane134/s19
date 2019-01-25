/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smondesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 13:41:16 by smondesi          #+#    #+#             */
/*   Updated: 2018/10/17 10:07:57 by smondesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*p;
	char	*v;

	p = (char *)src;
	v = (char *)dst;
	i = 0;
	while (len > 0)
	{
		v[i] = p[i];
		i++;
		len--;
	}
	return (dst);
}
