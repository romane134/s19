/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smondesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 14:59:39 by smondesi          #+#    #+#             */
/*   Updated: 2018/10/22 09:25:28 by smondesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*tab;
	unsigned int	i;

	i = 0;
	if (s != NULL && f != NULL)
	{
		tab = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
		if (tab == NULL)
			return (0);
		while (s[i])
		{
			tab[i] = f(i, s[i]);
			i++;
		}
		tab[i] = '\0';
		return (tab);
	}
	return (0);
}
