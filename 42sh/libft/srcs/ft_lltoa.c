/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjovanov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 08:31:33 by bjovanov          #+#    #+#             */
/*   Updated: 2019/01/03 08:31:33 by bjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	set_size_array(long long n)
{
	int		nb;

	nb = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= 10;
		nb++;
	}
	return (nb);
}

static void	set_array(char *nbr, long long n, int is_negative, int size_array)
{
	while (size_array + is_negative > 0)
	{
		nbr[(size_array + is_negative) - 1] = (n % 10) + 48;
		n /= 10;
		size_array--;
	}
}

/*
** NAME:
** 	ft_lltoa
**
** DESCRIPTION:
**	ft_lltoa() convertit une valeur de type long long en chaine de caractere
**	et la stocke dans une nouvelle zone de memoire (alloue avec malloc(3))
**
** SYNOPSIS:
**	int *ft_lltoa(long long n)
**
** PARAMS:
** 	n - la valeur a convertir
**
** RETURN VALUE:
**	(char*) la valeur convertie
*/

char		*ft_lltoa(long long n)
{
	char	*nbr;
	int		is_negative;
	int		size_array;

	is_negative = 0;
	if (n == LLONG_MIN)
		return (ft_strdup("-9223372036854775808"));
	if (n < 0)
	{
		is_negative = 1;
		n *= -1;
	}
	size_array = set_size_array(n);
	nbr = ft_strnew(size_array + is_negative);
	if (nbr == NULL)
		return (NULL);
	set_array(nbr, n, is_negative, size_array);
	if (is_negative == 1)
		nbr[0] = '-';
	return (nbr);
}
