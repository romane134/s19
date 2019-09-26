/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_2dtabdel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smondesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 19:34:07 by smondesi          #+#    #+#             */
/*   Updated: 2019/06/26 19:34:10 by smondesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_2darraydel(void **array, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		free(array[i]);
		i++;
	}
	free(array);
	array = NULL;
}

void	ft_2dstrdel(char ***str)
{
	int i;

	i = 0;
	while ((*str)[i])
	{
		ft_strdel(&((*str)[i]));
		i++;
	}
	free((*str));
	(*str) = NULL;
}
