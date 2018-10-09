/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 08:54:15 by rlucas-d          #+#    #+#             */
/*   Updated: 2018/10/08 09:47:58 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int result;
	long long int a;
	long long int neg;

	a = 0;
	result = 0;
	neg = 1;
	while (str[a] == ' ' || str[a] == '\t' || str[a] == '\n' || str[a] == '\r'
			|| str[a] == '\f' || str[a] == '\v')
		a++;
	if (str[a] == '-' || str[a] == '+')
	{
		if (str[a] == '-')
			neg = -1;
		a++;
	}
	while (str[a] >= 48 && str[a] <= 57)
	{
		result = result * 10 + (long long int)str[a] - '0';
		a++;
	}
	return (result * neg);
}
