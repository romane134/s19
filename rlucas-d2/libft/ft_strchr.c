/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smondesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 09:57:06 by smondesi          #+#    #+#             */
/*   Updated: 2018/10/11 14:52:47 by smondesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;

	i = 0;
	while (s[i] != c && s[i])
	{
		i++;
	}
	if (s[i] == c)
	{
		return ((char*)&s[i]);
	}
	else
		return (NULL);
}
