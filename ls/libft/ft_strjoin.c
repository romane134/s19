/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smondesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 12:36:27 by smondesi          #+#    #+#             */
/*   Updated: 2018/10/19 09:52:52 by smondesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	int		i;
	int		a;
	char	*c;

	i = 0;
	a = 0;
	if (s1 == NULL || s2 == NULL)
		return (0);
	len = ft_strlen(s1) + ft_strlen(s2);
	if ((c = ft_strnew(len)) == NULL)
		return (NULL);
	while (s1[i])
	{
		c[i] = s1[i];
		i++;
	}
	while (s2[a])
	{
		c[a + i] = s2[a];
		a++;
	}
	return (c);
}
