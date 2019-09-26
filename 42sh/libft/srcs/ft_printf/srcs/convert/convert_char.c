/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 16:18:56 by vjovanov          #+#    #+#             */
/*   Updated: 2018/11/19 15:24:33 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

static int		char_min_field_width(t_data *data)
{
	char	*tmp;
	long	length;
	long	min_width;

	min_width = (long)ft_atoll(data->min_field_width)
		+ ((long)ft_strlen(data->value) - 1);
	if (min_width > MAX_FIELD_WIDTH)
		return (1);
	length = (min_width < (long)ft_strlen(data->value_format)) ?
		(long)ft_strlen(data->value_format) : min_width;
	tmp = data->value_format;
	if (!(data->value_format = ft_strnew((size_t)length)))
		return (0);
	ft_memset(data->value_format, ' ', (size_t)length);
	ft_memcpy(&(data->value_format[length - (long)ft_strlen(tmp)]),
		tmp, ft_strlen(tmp));
	return (del_array(tmp));
}

static int		char_minus_flag(t_data *data, int flag_id)
{
	long	value;
	long	length;
	char	*tmp;

	value = (long)ft_atoll(&(data->flags[flag_id][1]))
	+ ((long)ft_strlen(data->value) - 1);
	if (value == -1)
		value = 0;
	if (!(tmp = (data->value_format == NULL) ?
		ft_strdup(data->value) : ft_strdup(data->value_format)))
		return (0);
	if (value < 0 || value > MAX_FIELD_WIDTH)
		return (1);
	if (value <= (long)ft_strlen(tmp))
		length = (long)ft_strlen(tmp);
	else
		length = value;
	ft_strdel(&(data->value_format));
	if (!(data->value_format = ft_strnew(length)))
		return (!del_array(tmp));
	ft_memset(data->value_format, 32, (size_t)length);
	ft_memcpy(data->value_format, tmp, ft_strlen(tmp));
	return (del_array(tmp));
}

static int		flags(t_data *data)
{
	int id;

	if ((id = has_flag("-", data->flags)) >= 0)
		if (!(char_minus_flag(data, id)))
			return (0);
	if (data->value_format == NULL)
		if ((data->value_format = ft_strdup(data->value)) == NULL)
			return (0);
	return (1);
}

int				convert_char(t_data *data)
{
	if (!flags(data))
		return (0);
	if (data->min_field_width != NULL)
		if (!(char_min_field_width(data)))
			return (0);
	return (1);
}
