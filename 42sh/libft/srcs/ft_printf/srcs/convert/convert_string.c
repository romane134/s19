/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_string.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 16:18:29 by vjovanov          #+#    #+#             */
/*   Updated: 2018/11/21 21:07:22 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

static int	flags(t_data *data)
{
	int id;

	if ((id = has_flag("-", data->flags)) >= 0)
		if (!(generic_minus_flag(data, id)))
			return (0);
	if (data->value_format == NULL)
		if ((data->value_format = ft_strdup(data->value)) == NULL)
			return (0);
	return (1);
}

static int	ft_stringjoin(char *tmp, t_data *data, long length, long precision)
{
	ft_memset(tmp, ' ', (size_t)length);
	ft_strncpy(tmp, data->value, (size_t)precision);
	free(data->value_format);
	if (!(data->value_format = ft_strdup(tmp)))
	{
		ft_strdel(&tmp);
		return (0);
	}
	return (del_array(tmp));
}

static int	precision(t_data *data)
{
	long	precision;
	char	*tmp;
	int		id;
	long	length;

	precision = (long)ft_atoll(data->precision);
	length = 0;
	if (precision >= (long)ft_strlen(data->value))
		return (1);
	if ((id = has_flag("-", data->flags)) >= 0
		&& precision < (long)ft_atoll(&(data->flags[id][1])))
	{
		tmp = ft_strnew((size_t)ft_atoll(&(data->flags[id][1])));
		length = (long)ft_atoll(&(data->flags[id][1]));
	}
	else
	{
		tmp = ft_strnew((size_t)precision);
		length = precision;
	}
	if (tmp == NULL)
		return (0);
	return (ft_stringjoin(tmp, data, length, precision));
}

int			convert_string(t_data *data)
{
	if (!(flags(data)))
		return (0);
	if (data->precision != NULL && (ft_atoll(data->precision) < MAX_FIELD_WIDTH
		&& ft_atoll(data->precision) >= 0))
		if (!(precision(data)))
			return (0);
	if (data->min_field_width != NULL)
		if (!(min_field_width(data)))
			return (0);
	return (1);
}
