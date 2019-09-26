/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_unsigned.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 16:19:25 by vjovanov          #+#    #+#             */
/*   Updated: 2018/11/21 21:07:29 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

static long	set_precision_len(long precision, char *tmp)
{
	if (precision <= (long)ft_strclen(tmp, ' '))
		return (-1);
	else
	{
		if (precision >= (long)ft_strlen(tmp))
			return (precision);
		else
			return ((long)ft_strlen(tmp));
	}
	return (0);
}

static int	precision(t_data *data)
{
	char	*tmp;
	long	precision;
	long	length;

	if (ft_atoll(data->precision) > MAX_FIELD_WIDTH ||
		ft_atoll(data->precision) < 0)
		return (1);
	precision = (long)ft_atoll(data->precision);
	tmp = data->value_format;
	if ((length = set_precision_len(precision, tmp)) < 0)
		return (1);
	if (!(data->value_format = ft_strnew(length)))
		return (0);
	ft_memset(data->value_format, '0', (size_t)length);
	if (length == precision)
		ft_memcpy(&(data->value_format[precision - ft_strclen(tmp, ' ')]),
			tmp, ft_strclen(tmp, ' '));
	else if (length == (long)ft_strlen(tmp))
		ft_memcpy(&(data->value_format[precision - ft_strclen(tmp, ' ')]),
			tmp, (length - precision) + ft_strclen(tmp, ' '));
	return (del_array(tmp));
}

static int	flags(t_data *data)
{
	int id;

	if ((id = has_flag("-", data->flags)) >= 0)
		if (!(generic_minus_flag(data, id)))
			return (0);
	if ((id = has_flag("0", data->flags)) >= 0 && data->precision == NULL)
		if (!(generic_zero_flag(data, id)))
			return (0);
	if ((id = has_flag("0", data->flags)) >= 0 && data->precision != NULL)
		if (!(data->min_field_width = ft_strdup(&(data->flags[id][1]))))
			return (0);
	if (data->value_format == NULL)
		if ((data->value_format = ft_strdup(data->value)) == NULL)
			return (0);
	return (1);
}

int			convert_unsigned(t_data *data)
{
	if (data->precision != NULL && ft_strequ(data->precision, "0")
		&& ft_strequ(data->value, "0"))
	{
		data->value_format = ft_strdupwc(data->value, '0');
		if (data->value_format == NULL)
			return (0);
	}
	if (!(flags(data)))
		return (0);
	if (data->precision != NULL)
		if (!(precision(data)))
			return (0);
	if (data->min_field_width != NULL)
		if (!(min_field_width(data)))
			return (0);
	return (1);
}
