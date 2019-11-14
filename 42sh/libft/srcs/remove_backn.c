/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_backn.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 16:27:02 by rlucas-d          #+#    #+#             */
/*   Updated: 2019/10/26 16:27:03 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			remove_backn(char **buffer)
{
	int			i;
	int			len;
	char		*tmp;

	i = 0;
	len = 0;
	while ((*buffer)[i] && (*buffer)[i] == '\n')
		i++;
	tmp = ft_strnew(ft_strlen(*buffer));
	while ((*buffer)[i])
	{
		tmp[len] = (*buffer)[i];
		i++;
		len++;
	}
	ft_strdel(buffer);
	*buffer = ft_strdup(tmp);
	ft_strdel(&tmp);
}
