/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjovanov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 08:13:18 by bjovanov          #+#    #+#             */
/*   Updated: 2019/01/03 08:13:19 by bjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long long	convert_to_ll(const char *str, int sign)
{
	int			i;
	long long	number;
	long long	overflow;

	i = 0;
	number = 0;
	while (ft_isdigit(str[i]))
	{
		overflow = number;
		number = (number * 10) + (str[i] - 48);
		if (overflow && (number ^ overflow) < 0)
			return ((sign == 1) ? -1 : 0);
		i++;
	}
	return ((long long)number * sign);
}

/*
** NAME:
** 	ft_atoll
**
** DESCRIPTION:
**	ft_atoll() convertit la chaine de caracteres, passee en parametres,
**	en long long.
**
** SYNOPSIS:
**	int ft_atoll(const char *nptr)
**
** PARAMS:
** 	nptr - chaine de caracteres a convertir
**
** RETURN VALUE:
**	(long long) la valeur convertie
*/

long long			ft_atoll(const char *str)
{
	int i;
	int sign;

	i = 0;
	sign = 1;
	while (str[i])
	{
		if (ft_isspace(str[i]))
			i++;
		else if (str[i] == '-' || str[i] == '+')
		{
			if (!ft_isdigit(str[i + 1]))
				return (0);
			sign = (str[i] == '-' ? -sign : sign);
			i++;
		}
		else
			break ;
	}
	return (convert_to_ll(&str[i], sign));
}
