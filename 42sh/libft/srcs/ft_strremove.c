/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strremove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjovanov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 08:51:53 by bjovanov          #+#    #+#             */
/*   Updated: 2019/01/03 08:51:54 by bjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strremove(const char *str, int start, int len)
{
	int		i;
	char	*new;
	int		strlen;

	strlen = ft_strlen(str);
	i = 0;
	if (start > strlen - 1)
		return (ft_strdup(""));
	if (len > strlen - start)
		len = strlen - start;
	new = ft_strnew(strlen - len);
	while (i < start && str[i])
	{
		new[i] = str[i];
		i++;
	}
	i += len;
	while (str[i])
	{
		new[i - len] = str[i];
		i++;
	}
	return (new);
}
