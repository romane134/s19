/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 15:17:13 by vjovanov          #+#    #+#             */
/*   Updated: 2018/12/11 15:17:15 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dtoa.h"

static void		fill_array(double n, char *nbr, int is_neg, int nb_before_comma)
{
	int			i;
	int			size_array;

	i = 0;
	size_array = set_size_array_d(n);
	if (is_neg == 1)
		nbr[i++] = '-';
	nbr[nb_before_comma + is_neg] = '.';
	n /= ft_exp_d(10, nb_before_comma - 1);
	while (i < size_array)
	{
		if (nbr[i] == '.')
			i++;
		nbr[i] = ((int)(n + 1e-9)) + 48;
		n *= 10;
		n -= ((nbr[i] - 48) * 10);
		i++;
	}
}

static int		check_binary(char *n_bin, char *nbr)
{
	char	*exponent;
	char	*mantisse;
	int		i;

	i = 0;
	if (n_bin[0] == '1')
		nbr[i++] = '-';
	exponent = ft_strndup(&n_bin[1], EXP_BIT_64);
	mantisse = ft_strndup(&n_bin[EXP_BIT_64 + 1], MANT_BIT_64);
	if (exponent == NULL || mantisse == NULL)
		return (0);
	if (ft_strchr(exponent, '0') == NULL)
	{
		if (ft_strchr(mantisse, '1') != NULL)
			ft_memcpy(&(nbr[i]), "nan", 3);
		else
			ft_memcpy(&(nbr[i]), "inf", 3);
	}
	else if (!(ft_strchr(exponent, '1')) && !(ft_strchr(mantisse, '1')))
		ft_memcpy(&(nbr[i]), "0.00", 4);
	ft_strdel(&exponent);
	ft_strdel(&mantisse);
	return (1);
}

static char		*convert_to_ieee754(double n)
{
	unsigned int	i;
	unsigned int	j;
	unsigned char	*val;
	char			*n_bin;
	unsigned long	sizeofn;

	val = (unsigned char*)&n;
	sizeofn = sizeof(n);
	if (!(n_bin = (char*)malloc(sizeof(char) * ((CHAR_BIT * sizeofn + 1)))))
		return (NULL);
	n_bin[CHAR_BIT * sizeof(n)] = '\0';
	i = CHAR_BIT * sizeof(n);
	j = 0;
	while (i--)
	{
		n_bin[j] = (val[i / CHAR_BIT] & (1 << (i % CHAR_BIT))) ? '1' : '0';
		j++;
	}
	return (n_bin);
}

/*
** formule de conversion :
** (-1)^Sign * (1 + mantisse) * 2^exposant
**
**
** double	ieee754_to_decimal(char *binary)
** {
** 	int exposant;
** 	double mantisse;
** 	int	i;
**
** 	i = 0;
** 	exposant = 0;
** 	while (i < EXP_BIT_64)
** 	{
** 		exposant += ((binary[(EXP_BIT_64 - i)] - 48) * ft_exp(2, i));
** 		i++;
** 	}
** 	exposant -= EXP_BIAS_64;
** 	i = EXP_BIT_64 + 1;
** 	while (i < (MANT_BIT_64 + (EXP_BIT_64 + 1)))
** 	{
**		mantisse += ((binary[i] - 48) * (1 / ft_exp(2, i - (EXP_BIT_64))));
** 		i++;
**	}
**	return (ft_exp(-1, 0) * (1 + mantisse) * ft_exp(2, exposant));
** }
*/

/*
** NAME:
** 	ft_dtoa
**
** DESCRIPTION:
**	ft_dtoa() convertit une valeur de type double en chaine de caractere
**	et la stocke dans une nouvelle zone de memoire (alloue avec malloc(3))
**
** SYNOPSIS:
**	int *ft_dtoa(double n)
**
** PARAMS:
** 	n - la valeur a convertir
**
** RETURN VALUE:
**	(char*) la valeur convertie
*/

char			*ft_dtoa(double n)
{
	char		*nbr;
	char		*n_bin;
	int			is_neg;

	if (!(n_bin = convert_to_ieee754(n)))
		return (NULL);
	nbr = ft_strnew(5);
	if (!check_binary(n_bin, nbr))
		return (NULL);
	ft_strdel(&n_bin);
	if (nbr[0] != '\0' && !ft_strequ(nbr, "-"))
		return (nbr);
	ft_strdel(&nbr);
	is_neg = (n > 0) ? 0 : 1;
	n *= (is_neg == 1) ? -1 : 1;
	if (!(nbr = ft_strnew(set_size_array_d(n))))
		return (NULL);
	fill_array(n, nbr, is_neg, set_before_comma_d(n));
	return (nbr);
}
