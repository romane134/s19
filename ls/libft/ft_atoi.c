/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smondesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 14:11:54 by smondesi          #+#    #+#             */
/*   Updated: 2018/10/23 11:17:41 by smondesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	size_t	i;
	long	num;
	int		p;
	long	count;

	p = 1;
	num = 0;
	i = 0;
	while (str[i] == '\f' || str[i] == '\v' || str[i] == '\r' ||
				str[i] == '\n' || str[i] == '\t' || str[i] == ' ')
		i++;
	if (str[i] == '-')
		p = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		count = num;
		num = num * 10 + ((str[i] - 48) * p);
		if (count && (count ^ num) < 0)
			return ((p == -1) ? 0 : -1);
		i++;
	}
	return ((int)num);
}
