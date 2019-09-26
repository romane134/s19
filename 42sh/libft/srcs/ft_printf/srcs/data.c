/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 22:05:40 by bjovanov          #+#    #+#             */
/*   Updated: 2018/11/21 22:56:01 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void			set_data(t_data *data)
{
	int i;

	i = -1;
	data->identifier = 0;
	while (++i < NB_FLAGS + 1)
		data->flags[i] = NULL;
	i = -1;
	while (++i < NB_CONVERSION_FLAGS + 1)
		data->conversion_flags[i] = NULL;
	data->precision = NULL;
	data->min_field_width = NULL;
	data->s_fmt_new = NULL;
	data->s_fmt_orig = NULL;
	data->value_format = NULL;
	data->value = NULL;
}

void			free_data(t_data *data)
{
	int i;
	int size;

	i = -1;
	data->identifier = 0;
	size = ft_array_length((void**)data->flags);
	while (++i < size)
		ft_strdel(&(data->flags[i]));
	i = -1;
	size = ft_array_length((void**)data->conversion_flags);
	while (++i < size)
		ft_strdel(&(data->conversion_flags[i]));
	ft_strdel(&(data->precision));
	ft_strdel(&(data->min_field_width));
	ft_strdel(&(data->s_fmt_new));
	ft_strdel(&(data->s_fmt_orig));
	ft_strdel(&(data->value_format));
	ft_strdel(&(data->value));
}

static int		fill_data_extend(t_data *data, va_list ap, int i)
{
	int ret;

	ret = 0;
	if ((ret = is_precision((const char*)&(data->s_fmt_new[i]))) > 0)
		data->precision = fill_precision(&(data->s_fmt_new[i]), ap, ret);
	else if ((ret = is_min_field_width((const char*)&(data->s_fmt_new[i]))) > 0)
		data->min_field_width = fill_field_width(
			&(data->s_fmt_new[i]), ap, ret);
	else if ((ret = is_identifier(data->s_fmt_new[i])) > 0)
		data->identifier = fill_id(&(data->s_fmt_new[i]));
	return (ret);
}

/*
** i[0] = i
** i[1] = j
** i[2] = k
** i[3] = ret
*/

static int		fill_data_flags(t_data *d, va_list ap, int *i, char **tmp)
{
	if ((i[3] = is_flag((const char*)&(d->s_fmt_new[i[0]]))) > 0)
	{
		if (is_acceparrayle_flag(d->s_fmt_new[
			(int)ft_strlen(d->s_fmt_new) - 1], d->s_fmt_new[i[0]]))
		{
			if ((*tmp = fill_flags(&(d->s_fmt_new[i[0]]), ap, i[3])) == NULL)
				return (0);
			d->flags[i[1]++] = ft_strdup(*tmp);
		}
	}
	else if ((i[3] = is_conversion_flag(
		(const char*)&(d->s_fmt_new[i[0]]))) > 0)
	{
		if (is_acceparrayle_conv_flag(
			d->s_fmt_new[(int)ft_strlen(d->s_fmt_new) - 1],
			&(d->s_fmt_new[i[0]]), i[3]))
		{
			if ((*tmp = fill_conv_flags(&(d->s_fmt_new[i[0]]), i[3])) == NULL)
				return (0);
			d->conversion_flags[i[2]++] = ft_strdup(*tmp);
		}
	}
	else
		i[3] = fill_data_extend(d, ap, i[0]);
	return (i[3]);
}

/*
** i[0] = i
** i[1] = j
** i[2] = k
** i[3] = ret
*/

int				fill_data(t_data *data, va_list ap)
{
	int		i[4];
	char	*tmp;

	ft_intset(i, 4, 0);
	i[0] = 1;
	tmp = NULL;
	while (data->s_fmt_new[i[0]])
	{
		if (fill_data_flags(data, ap, i, &tmp) == 0)
			return (0);
		ft_memdel((void**)&tmp);
		i[0] += i[3];
	}
	tmp = NULL;
	return (dispatcher(data, ap));
}
