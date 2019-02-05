/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smondesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 11:40:41 by smondesi          #+#    #+#             */
/*   Updated: 2018/10/19 11:02:27 by smondesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	int			i;
	int			a;
	int			k;
	char		*c;

	if (s == NULL)
		return (0);
	k = ft_strlen(s);
	i = 0;
	a = -1;
	while ((s[i] == ' ' || s[i] == '\n' || s[i] == '\t') && s[i])
		i++;
	while ((s[k - 1] == ' ' || s[k - 1] == '\n' || s[k - 1] == '\t') && k > 0)
		k--;
	if (s[i] == '\0')
		return (ft_strnew(0));
	if ((c = (char*)malloc(sizeof(char) * ((k - i) + 1))) == NULL)
		return (NULL);
	while ((a++) < (k - i - 1))
		c[a] = s[i + a];
	c[a++] = '\0';
	return (c);
}
