/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdupwc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjovanov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 08:36:33 by bjovanov          #+#    #+#             */
/*   Updated: 2019/01/03 08:36:34 by bjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdupwc(char *str, char ban)
{
	size_t	new_size;
	size_t	i;
	size_t	j;
	char	*new_str;

	if (str == NULL)
		return (NULL);
	new_size = 0;
	i = -1;
	j = -1;
	while (str[++i])
		if (str[i] != ban)
			new_size++;
	if (!(new_str = ft_strnew(new_size)))
		return (NULL);
	i = -1;
	while (str[++i])
		if (str[i] != ban)
			new_str[++j] = str[i];
	return (new_str);
}
