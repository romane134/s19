/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 10:38:09 by rlucas-d          #+#    #+#             */
/*   Updated: 2018/10/08 02:59:48 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count(size_t a, size_t b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

size_t			ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;

	dst_len = ft_count(size, ft_strlen((const char *)dst));
	src_len = ft_strlen(src);
	if (dst_len == size)
		return (size + src_len);
	if (src_len < size - dst_len)
		ft_strncat(dst, src, src_len + 1);
	else
	{
		ft_strncat(dst, src, size - dst_len - 1);
		dst[size - 1] = '\0';
	}
	return (dst_len + src_len);
}
