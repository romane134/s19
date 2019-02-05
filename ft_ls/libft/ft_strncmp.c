/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smondesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 14:35:38 by smondesi          #+#    #+#             */
/*   Updated: 2018/10/18 11:28:03 by smondesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t			i;
	unsigned char	*z1;
	unsigned char	*z2;

	z1 = (unsigned char *)str1;
	z2 = (unsigned char *)str2;
	i = 0;
	if (n == 0)
		return (0);
	while (str1[i] && str2[i] && n > i && str1[i] == str2[i])
		i++;
	if (i == n)
		return (0);
	if (str1[i] != str2[i])
		return (z1[i] - z2[i]);
	return (0);
}
