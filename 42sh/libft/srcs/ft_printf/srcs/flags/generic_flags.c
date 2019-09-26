/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generic_flags.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 20:21:10 by vjovanov          #+#    #+#             */
/*   Updated: 2018/11/19 23:16:29 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

int		generic_minus_flag(t_data *data, int flag_id)
{
	long	value;
	long	length;
	char	*tmp;

	value = (long)ft_atoll(&(data->flags[flag_id][1]));
	if (value < 0 || value > MAX_FIELD_WIDTH)
		return (1);
	if (!(tmp = (data->value_format == NULL) ?
		ft_strdup(data->value) : ft_strdup(data->value_format)))
		return (0);
	if (value <= (int)ft_strlen(tmp))
		length = (int)ft_strlen(tmp);
	else
		length = value;
	ft_strdel(&data->value_format);
	if (!(data->value_format = ft_strnew(length)))
		return (!del_array(tmp));
	ft_memset(data->value_format, 32, (size_t)length);
	ft_memcpy(data->value_format, tmp, ft_strlen(tmp));
	ft_strdel(&tmp);
	return (1);
}

int		generic_plus_flag(t_data *data)
{
	char *tmp;

	tmp = (data->value_format == NULL) ?
		ft_strdup(data->value) : ft_strdup(data->value_format);
	if (tmp == NULL)
		return (0);
	if (data->value[0] == '-')
	{
		if (data->value_format != NULL)
			ft_strdel(&(data->value_format));
		data->value_format = ft_strdup(tmp);
		ft_strdel(&tmp);
		if (data->value_format == NULL)
			return (0);
	}
	else if (data->value[0] != '-')
	{
		if (data->value_format != NULL)
			ft_strdel(&(data->value_format));
		data->value_format = ft_strjoin("+", tmp);
		ft_strdel(&tmp);
		if (data->value_format == NULL)
			return (0);
	}
	return (1);
}

int		generic_zero_flag(t_data *data, int flag_id)
{
	long	value;
	long	length;
	char	*tmp;
	long	i;

	if (!(tmp = (data->value_format == NULL) ?
		ft_strdup(data->value) : ft_strdup(data->value_format)))
		return (0);
	i = (tmp[0] == '-' || tmp[0] == '+' || tmp[0] == ' ') ? 1 : 0;
	value = (long)ft_atoll(data->flags[flag_id]);
	length = (value <= (int)ft_strlen(tmp)) ?
		(int)ft_strlen(tmp) + i : value + i;
	ft_strdel(&(data->value_format));
	if (!(data->value_format = ft_strnew(length)))
		return (!del_array(tmp));
	ft_memset(data->value_format, '0', (size_t)length);
	if (tmp[0] == '-')
		data->value_format[0] = '-';
	else if (tmp[0] == '+')
		data->value_format[0] = '+';
	else if (tmp[0] == ' ')
		data->value_format[0] = ' ';
	ft_memcpy(&(data->value_format[length - (int)ft_strlen(tmp)]),
		&(tmp[i]), ft_strlen(tmp));
	return (del_array(tmp));
}

int		generic_space_flag(t_data *data)
{
	char *tmp;

	if (has_flag("+", data->flags) >= 0)
		return (1);
	if (!(tmp = (data->value_format == NULL) ?
		ft_strdup(data->value) : ft_strdup(data->value_format)))
		return (0);
	if (tmp[0] == '-')
	{
		if (data->value_format != NULL)
			ft_strdel(&(data->value_format));
		data->value_format = ft_strdup(tmp);
		ft_strdel(&tmp);
	}
	else if (data->value[0] != '-')
	{
		if (data->value_format != NULL)
			ft_strdel(&(data->value_format));
		data->value_format = ft_strjoin(" ", tmp);
		ft_strdel(&tmp);
	}
	return (data->value_format == NULL ? 0 : 1);
}
