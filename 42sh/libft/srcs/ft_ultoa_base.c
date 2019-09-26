/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjovanov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 08:42:46 by bjovanov          #+#    #+#             */
/*   Updated: 2019/01/03 08:42:47 by bjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	set_size_array(unsigned long number, int base)
{
	int size_array;

	size_array = 0;
	while (number > 0)
	{
		number /= base;
		size_array++;
	}
	return (size_array);
}

static void	convert(char *nbr, unsigned long number, int base)
{
	int length;

	length = set_size_array(number, base);
	while (number > 0)
	{
		if (number % base >= 10)
			nbr[length - 1] = ((number % base) + 'a') - 10;
		else
			nbr[length - 1] = (number % base) + 48;
		number /= base;
		length--;
	}
}

char		*ft_ultoa_base(unsigned long number, int base)
{
	char	*nbr;
	int		length;

	if (number == 0)
		return (ft_strdup("0"));
	if (base < 2)
		return (NULL);
	length = set_size_array(number, base);
	if ((nbr = ft_strnew(length)) == NULL)
		return (NULL);
	convert(nbr, number, base);
	return (nbr);
}
