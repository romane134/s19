/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 08:54:15 by rlucas-d          #+#    #+#             */
/*   Updated: 2018/10/05 08:46:29 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		atoi(const char *str)
{
	int result;
	int a;
	int neg;

	a = 0;
	result = 0;
	neg = 1;
	while (str[a] == ' ' || str[a] == '\t' || str[a] == '\n' || str[a] == '\r'
			|| str[a] == '\f' || str[a] == '\v')
		a++;
	if (str[a] == '-')
	{
		neg = -1;
		a++;
	}
	if (str[a] == '+')
		a++;
	while (str[a] >= 48 && str[a] <= 57)
	{
		result = result * 10 + str[a] - '0';
		a++;
	}
	return (result * neg);
}
