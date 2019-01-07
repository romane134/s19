/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smondesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 09:50:01 by smondesi          #+#    #+#             */
/*   Updated: 2018/10/24 13:52:58 by smondesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t		ft_taille(long n, int base)
{
	size_t taille;

	taille = 0;
	if (n == 0)
		taille = 1;
	while (n > 0)
	{
		n = n / base;
		taille++;
	}
	return (taille);
}

static char			*do_str(size_t taille, char *str, int base, int nb)
{
	int	a;

	while (taille > 0)
	{
		taille--;
		a = (nb % base);
		if (a >= 0 && a <= 9)
			str[taille] = a + '0';
		if (a > 9)
			str[taille] = a + 55;
		nb = nb / base;
	}
	return (str);
}

char				*st_itoa_base(int n, int base)
{
	size_t	taille;
	long	nb;
	char	*str;

	nb = n;
	taille = ft_taille(nb, base);
	if ((str = ft_strnew(taille)) == NULL)
		return (NULL);
	str = do_str(taille, str, base, nb);
	return (str);
}
