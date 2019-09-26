/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 14:12:28 by vjovanov          #+#    #+#             */
/*   Updated: 2018/12/11 16:28:46 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		is_identifier(const char c)
{
	int i;

	i = 0;
	while (i < NB_IDENTIFIERS)
	{
		if (get_identifiers()[i].identifier == c)
			return (1);
		i++;
	}
	return (0);
}

int		is_flag(const char *c)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (*c == '0' || *c == '-')
	{
		if (c[j + 1] == '*')
			return (2);
		while ((ft_isdigit(c[j + 1]) && *c != '\0'))
			j++;
		return (j + 1);
	}
	while (i < NB_FLAGS)
	{
		if (*c == get_flags()[i][0])
			return (1);
		i++;
	}
	return (0);
}

int		is_conversion_flag(const char *c)
{
	int		i;
	size_t	length;

	i = 0;
	while (i < NB_CONVERSION_FLAGS)
	{
		length = ft_strlen(&(get_conversion_flags()[i][0]));
		if (ft_strncmp(c, &(get_conversion_flags()[i][0]), length) == 0)
			return ((int)length);
		i++;
	}
	return (0);
}

int		is_precision(const char *c)
{
	int nb_digits;

	nb_digits = 0;
	if (*c == '.')
	{
		if (*(c + 1) == '*')
			return (2);
		while (ft_isdigit(*(c + 1)))
		{
			nb_digits++;
			c++;
		}
		return (nb_digits + 1);
	}
	return (-1);
}

int		is_min_field_width(const char *c)
{
	int i;

	i = 0;
	if (*c == '*')
		return (1);
	while (ft_isdigit(*c) && *c != '\0')
	{
		i++;
		c++;
	}
	return (i);
}
