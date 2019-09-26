/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjovanov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 08:42:37 by bjovanov          #+#    #+#             */
/*   Updated: 2019/01/03 08:42:38 by bjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	set_size_array(unsigned long n)
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

/*
** NAME:
** 	ft_ultoa
**
** DESCRIPTION:
**	ft_ultoa() convertit une valeur de type unsigned long en chaine de caractere
**	et la stocke dans une nouvelle zone de memoire (alloue avec malloc(3))
**
** SYNOPSIS:
**	int *ft_ultoa(unsigned long n)
**
** PARAMS:
** 	n - la valeur a convertir
**
** RETURN VALUE:
**	(char*) la valeur convertie
*/

char		*ft_ultoa(unsigned long n)
{
	char	*nbr;
	int		size_array;

	size_array = set_size_array(n);
	nbr = ft_strnew(size_array);
	if (nbr == NULL)
		return (NULL);
	while (size_array > 0)
	{
		nbr[size_array - 1] = (n % 10) + 48;
		n /= 10;
		size_array--;
	}
	return (nbr);
}
