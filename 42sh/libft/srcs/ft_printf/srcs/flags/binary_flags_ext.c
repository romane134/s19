/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_flags_ext.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 14:44:37 by vjovanov          #+#    #+#             */
/*   Updated: 2018/12/12 14:44:38 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

static long	ft_exp(long n, int exp)
{
	long		value_exp;
	int			i;

	value_exp = n;
	i = 0;
	if (exp == 0)
		return (1);
	while (i < exp - 1)
	{
		value_exp *= n;
		i++;
	}
	return (value_exp);
}

static long	set_precision_size(t_data *data)
{
	int i;

	i = 3;
	while (ft_exp(2, i) < ft_atoll(data->precision) ||
		ft_exp(2, i) < (long)ft_strlen(data->value_format))
		i++;
	ft_strdel(&(data->precision));
	if ((data->precision = ft_strdup(ft_ltoa(ft_exp(2, i)))) == NULL)
		return (0);
	return (ft_exp(2, i));
}

static long	set_zero_size(t_data *data, int id)
{
	int i;

	i = 3;
	while (ft_exp(2, i) < ft_atoll(&(data->flags[id][1])) ||
		ft_exp(2, i) < (long)ft_strlen(data->value_format))
		i++;
	ft_strdel(&(data->flags[id]));
	if ((data->flags[id] = ft_strjoin("0", ft_ltoa(ft_exp(2, i)))) == NULL)
		return (0);
	return (ft_exp(2, i));
}

long		set_size_binary(t_data *data)
{
	int		id;
	int		i;

	i = 3;
	if ((id = has_flag("0", data->flags)) < 0 && data->precision == NULL)
		while (ft_exp(2, i) < (long)ft_strlen(
			&(data->value_format[(data->value_format[0] == '-') ? 1 : 0])))
			i++;
	else
	{
		if (((id = has_flag("0", data->flags)) >= 0 && data->precision != NULL)
			|| (data->precision != NULL && has_flag("0", data->flags) < 0))
			return (set_precision_size(data));
		else if ((id = has_flag("0", data->flags)) >= 0 &&
			data->precision == NULL)
			return (set_zero_size(data, id));
	}
	return (ft_exp(2, i));
}

void		convert_two_complement(t_data *data)
{
	int i;

	i = 0;
	while (data->value_format[i])
	{
		if (data->value_format[i] == '0')
			data->value_format[i] = '1';
		else
			data->value_format[i] = '0';
		i++;
	}
	i--;
	data->value_format[i] += 1;
	while (data->value_format[i] == '2')
	{
		data->value_format[i] -= 2;
		data->value_format[i - 1] += 1;
		i--;
	}
}
