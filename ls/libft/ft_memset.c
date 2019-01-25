/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smondesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 15:30:14 by smondesi          #+#    #+#             */
/*   Updated: 2018/10/19 12:12:40 by smondesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t len)
{
	size_t			i;
	unsigned char	*p;

	p = (unsigned char *)str;
	i = 0;
	while (len > i)
	{
		p[i] = (unsigned char)c;
		i++;
	}
	return (str);
}
