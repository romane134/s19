/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 23:01:13 by rlucas-d          #+#    #+#             */
/*   Updated: 2018/10/05 03:10:03 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strequ(char const *s1, char const *s2)
{
	if (!s1 || !s2)
		return (0);
	if (!s1 && !s2)
		return (1);
	while (*s1)
	{
		if (*s1 != *s2)
			return (0);
		else
		{
			s1++;
			s2++;
		}
	}
	if (*s1 == *s2)
		return (1);
	return (0);
}
