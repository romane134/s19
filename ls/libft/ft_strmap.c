/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smondesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 14:50:23 by smondesi          #+#    #+#             */
/*   Updated: 2018/10/22 09:24:14 by smondesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*tab;
	int		i;

	i = 0;
	if (s != NULL && f != NULL)
	{
		tab = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
		if (tab == NULL)
			return (0);
		while (s[i])
		{
			tab[i] = f(s[i]);
			i++;
		}
		tab[i] = '\0';
		return (tab);
	}
	else
		return (0);
}
