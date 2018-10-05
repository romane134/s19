/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 18:56:36 by rlucas-d          #+#    #+#             */
/*   Updated: 2018/10/04 19:04:03 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		a;
	char	*str;

	str = (char *)s;
	a = 0;
	while (str[a] != '\0')
		a++;
	str[a] = '\0';
	while (a > 0 && str[a] != (char)c)
		a--;
	if (str[a] == (char)c)
		return (&str[a]);
	return (NULL);
}
