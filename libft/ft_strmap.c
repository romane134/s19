/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 18:17:05 by rlucas-d          #+#    #+#             */
/*   Updated: 2018/10/09 16:36:00 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(const char *s, char (*f)(char))
{
	char	*str;
	int		a;

	a = 0;
	if (!s || !(str = ft_strnew(ft_strlen(s))))
		return (NULL);
	while (s[a])
	{
		str[a] = f(s[a]);
		a++;
	}
	return (str);
}
