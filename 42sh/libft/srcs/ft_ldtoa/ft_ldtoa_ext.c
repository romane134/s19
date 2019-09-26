/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ldtoa_ext.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 12:55:41 by vjovanov          #+#    #+#             */
/*   Updated: 2018/12/07 13:15:23 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ldtoa.h"

long double	ft_exp_ld(long double n, int exp)
{
	long double	value_exp;
	int			i;

	value_exp = n;
	i = 0;
	if (exp == 0)
		return (1.0);
	while (i < exp - 1)
	{
		value_exp *= n;
		i++;
	}
	return (value_exp);
}

int			set_size_array_ld(long double n)
{
	int		nb;

	nb = 0;
	if (n == 0)
		return (1);
	while (n > 0.0)
	{
		n /= 10;
		nb++;
	}
	return (nb + 1);
}

int			set_before_comma_ld(long double n)
{
	int			nb_before_comma;
	long double	a;

	nb_before_comma = 0;
	a = 1.0;
	if (n < a)
		return (1);
	while (n >= a && a <= LDBL_MAX)
	{
		nb_before_comma++;
		a *= 10.0;
	}
	return (nb_before_comma);
}
