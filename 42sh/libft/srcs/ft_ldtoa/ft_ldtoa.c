/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ldtoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 12:55:29 by vjovanov          #+#    #+#             */
/*   Updated: 2018/12/07 14:09:38 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ldtoa.h"

static void	fill_array(long double n, char *nbr, int is_neg, int nb_bef_comma)
{
	int			i;
	int			size_array;

	i = 0;
	size_array = set_size_array_ld(n);
	if (is_neg == 1)
		nbr[i++] = '-';
	nbr[nb_bef_comma + is_neg] = '.';
	n /= ft_exp_ld(10, nb_bef_comma - 1);
	while (i < size_array)
	{
		if (nbr[i] == '.')
			i++;
		nbr[i] = (int)n + 48;
		n *= 10;
		n -= ((nbr[i] - 48) * 10);
		i++;
	}
}

static int	check_binary(char *n_bin, char *nbr)
{
	char	*exponent;
	char	*mantisse;
	int		i;

	i = 0;
	if (n_bin[0] == '1')
		nbr[i++] = '-';
	exponent = ft_strndup(&n_bin[1], EXP_BIT_64_LD);
	mantisse = ft_strndup(&n_bin[EXP_BIT_64_LD + 1], MANT_BIT_64_LD);
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

static char	*convert_to_ieee754(long double n)
{
	unsigned int	i;
	unsigned int	j;
	unsigned char	*val;
	char			*n_bin;

	val = (unsigned char*)&n;
	if (!(n_bin = (char*)malloc(sizeof(char) *
		((CHAR_BIT * EXTENDED_PRECISION_SIZEOF) + 1))))
		return (NULL);
	n_bin[CHAR_BIT * EXTENDED_PRECISION_SIZEOF] = '\0';
	i = CHAR_BIT * EXTENDED_PRECISION_SIZEOF;
	j = 0;
	while (i--)
	{
		n_bin[j] = (val[i / CHAR_BIT] & (1 << (i % CHAR_BIT)))
			? '1' : '0';
		j++;
	}
	return (n_bin);
}

/*
** formule de conversion :
** (-1)^Sign * (1 + mantisse) * 2^exposant
**
**
** long double	ieee754_to_decimal(char *binary)
** {
** 	int exposant;
** 	long double mantisse;
** 	int	i;
**
** 	i = 0;
** 	exposant = 0;
** 	while (i < EXP_BIT_64_LD)
** 	{
** 		exposant += ((binary[(EXP_BIT_64_LD - i)] - 48) * ft_exp_ld(2, i));
** 		i++;
** 	}
** 	exposant -= EXP_BIAS_64_LD;
** 	i = EXP_BIT_64_LD + 2;
** 	mantisse = 0.0;
** 	while (i < (MANT_BIT_64_LD + (EXP_BIT_64_LD + 1)))
** 	{
** 		mantisse += ((binary[i] - 48) *
**								(1 / ft_exp_ld(2, i - (EXP_BIT_64_LD + 1))));
** 		i++;
** 	}
** 	return (ft_exp_ld(-1, 0) * (1 + mantisse) * ft_exp_ld(2, exposant));
** }
*/

/*
** NAME:
** 	ft_ldtoa
**
** DESCRIPTION:
**	ft_ldtoa() convertit une valeur de type long double en chaine de caractere
**	et la stocke dans une nouvelle zone de memoire (alloue avec malloc(3))
**
** SYNOPSIS:
**	int *ft_ldtoa(long double n)
**
** PARAMS:
** 	n - la valeur a convertir
**
** RETURN VALUE:
**	(char*) la valeur convertie
*/

char		*ft_ldtoa(long double n)
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
	if (!(nbr = ft_strnew(set_size_array_ld(n))))
		return (NULL);
	fill_array(n, nbr, is_neg, set_before_comma_ld(n));
	return (nbr);
}
