/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smondesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 13:54:36 by smondesi          #+#    #+#             */
/*   Updated: 2018/10/19 11:37:24 by smondesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*new;
	size_t	i;

	i = 0;
	new = (char*)malloc(sizeof(char) * (size + 1));
	if (new == NULL)
		return (0);
	while (i < (size + 1))
	{
		new[i] = '\0';
		i++;
	}
	return (new);
}
