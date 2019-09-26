/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_binary.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 12:28:46 by vjovanov          #+#    #+#             */
/*   Updated: 2018/12/12 12:28:47 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

static long	set_precision_len(long precision, char *tmp)
{
	if (precision <= (long)ft_strclen(tmp, ' '))
		return (-2);
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
	long	prec;
	long	length;
	int		i;

	if (ft_atoll(data->precision) > MAX_FIELD_WIDTH ||
		ft_atoll(data->precision) < 0)
		return (1);
	prec = (long)ft_atoll(data->precision);
	tmp = data->value_format;
	i = (tmp[0] == '-' || tmp[0] == '+' || tmp[0] == ' ') ? 1 : 0;
	if ((length = set_precision_len(prec, &(tmp[i])) + i) < 0)
		return (1);
	if (!(data->value_format = ft_strnew((size_t)length)))
		return (0);
	ft_memset(data->value_format, '0', (size_t)length);
	if (tmp[0] == '-' || tmp[0] == '+' || tmp[0] == ' ')
		data->value_format[0] = tmp[0];
	if (length == prec + i)
		ft_memcpy(&(data->value_format[prec + i - ft_strclen(&(tmp[i]), ' ')]),
			&(tmp[i]), ft_strclen(&(tmp[i]), ' '));
	else if (length == (long)ft_strlen(tmp))
		ft_memcpy(&(data->value_format[prec + i - ft_strclen(&(tmp[i]), ' ')]),
			&(tmp[i]), ((length - prec) - i) + ft_strclen(&(tmp[i]), ' '));
	return (del_array(tmp));
}

static int	flags(t_data *data)
{
	int id;

	if ((id = has_flag("#", data->flags)) >= 0)
		if (!(binary_hashtag_flag(data)))
			return (0);
	if ((id = has_flag("-", data->flags)) >= 0)
		if (!(generic_minus_flag(data, id)))
			return (0);
	if ((id = has_flag("+", data->flags)) >= 0 &&
		has_flag("#", data->flags) < 0)
		if (!(generic_plus_flag(data)))
			return (0);
	if ((id = has_flag(" ", data->flags)) >= 0 &&
		has_flag("#", data->flags) < 0)
		if (!(generic_space_flag(data)))
			return (0);
	if ((id = has_flag("0", data->flags)) >= 0 && data->precision == NULL)
		if (!(generic_zero_flag(data, id)))
			return (0);
	if ((id = has_flag("0", data->flags)) >= 0 && data->precision != NULL)
		if (!(data->min_field_width = ft_strdup(&(data->flags[id][1]))))
			return (0);
	return (1);
}

int			convert_binary(t_data *data)
{
	char *nb;

	if (!(nb = ft_lltoa_base(ft_atoll(data->value), 2)))
		return (0);
	if (!(data->value_format = ft_strdup(nb)))
		return (!del_array(nb));
	ft_strdel(&nb);
	if (!(flags(data)))
		return (0);
	if (data->precision != NULL && has_flag("#", data->flags) < 0)
		if (!(precision(data)))
			return (0);
	if (data->min_field_width != NULL)
		if (!(min_field_width(data)))
			return (0);
	return (1);
}
