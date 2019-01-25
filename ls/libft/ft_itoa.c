/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smondesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 14:48:42 by smondesi          #+#    #+#             */
/*   Updated: 2018/10/24 14:01:42 by smondesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t		ft_taille(long n)
{
	size_t taille;

	taille = 0;
	if (n == 0)
		taille = 1;
	while (n > 0)
	{
		n = n / 10;
		taille++;
	}
	return (taille);
}

char				*ft_itoa(int n)
{
	size_t	taille;
	int		p;
	long	nb;
	char	*str;

	p = 0;
	nb = n;
	if (nb < 0)
	{
		p = 1;
		nb = nb * -1;
	}
	taille = ft_taille(nb);
	if ((str = (char*)malloc(sizeof(char) * (taille + p + 1))) == NULL)
		return (0);
	if (p == 1)
		str[0] = '-';
	str[taille + p] = '\0';
	while (taille > 0)
	{
		taille--;
		str[taille + p] = (nb % 10) + '0';
		nb = nb / 10;
	}
	return (str);
}
