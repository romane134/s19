/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_double.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 16:19:46 by vjovanov          #+#    #+#             */
/*   Updated: 2018/11/21 22:19:20 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

static char	*ft_pow_ext(char *number, char *new_n, int report)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	tmp = (report == 1) ? ft_strjoin("1", new_n) : ft_strdup(new_n);
	if (tmp == NULL)
		return (NULL);
	tmp3 = ft_strndup(tmp, ft_strclen(number, '.') + report);
	tmp2 = ft_strjoin(tmp3, ".");
	ft_strdel(&tmp);
	ft_strdel(&tmp3);
	if (tmp2 == NULL)
	{
		ft_strdel(&number);
		ft_strdel(&new_n);
		return (NULL);
	}
	tmp3 = ft_strndup(&(new_n[ft_strclen(number, '.')]),
		ft_strlen(&(new_n[ft_strclen(number, '.')])));
	tmp = ft_strjoin(tmp2, tmp3);
	ft_strdel(&tmp3);
	ft_strdel(&new_n);
	ft_strdel(&number);
	ft_strdel(&tmp2);
	return (tmp == NULL ? NULL : tmp);
}

/*
** array[0] = n
** array[1] = report
*/

static char	*ft_pow(char *number, long precision)
{
	char	*new_n;
	long	array[2];

	array[1] = 0;
	if (!(new_n = ft_strremove(number, (int)ft_strclen(number, '.'), 1)))
		return (NULL);
	array[0] = (((long)ft_strclen(number, '.') + precision) - 1) + 1;
	while (--array[0] >= 0)
		if (new_n[array[0] + 1] >= '5' || array[1] == 1)
		{
			if ((new_n[array[0]] + 1) > '9' && (new_n[array[0]] = '0') == '0')
				array[1] = 1;
			else
			{
				new_n[array[0]]++;
				array[1] = 0;
				break ;
			}
		}
		else
		{
			array[1] = 0;
			break ;
		}
	return (ft_pow_ext(number, new_n, array[1]));
}

/*
** int p = precision
*/

static int	precision(t_data *data)
{
	char			*tmp;
	char			*temp;
	long			p;

	if (ft_atoll(data->precision) > MAX_FIELD_WIDTH ||
		ft_atoll(data->precision) < 0)
		return (1);
	p = (long)ft_atoll(data->precision);
	if (p < (long)ft_strlen(&(data->value[ft_strclen(data->value, '.') + 1])))
		if (!(data->value = ft_pow(data->value, p)))
			return (0);
	if ((tmp = ft_strnew((size_t)p)) == NULL)
		return (0);
	if (ft_memset(tmp, '0', p) != NULL && p > (long)ft_strlen(
		&(data->value[ft_strclen(data->value, '.') + 1])))
		ft_memcpy(tmp, ft_strchr(data->value, '.') + 1,
			ft_strlen(ft_strchr(data->value, '.') + 1));
	else
		ft_memcpy(tmp, ft_strchr(data->value, '.') + 1, (size_t)p);
	if (!(temp = ft_strndup(data->value, ft_strclen(data->value, '.') + 1)))
		return (0);
	if ((data->value_format = ft_strjoin(temp, tmp)) == NULL)
		return (0);
	ft_strdel(&tmp);
	return (del_array(temp));
}

static int	flags(t_data *data)
{
	int id;

	if ((id = has_flag(" ", data->flags)) >= 0)
		if (!(generic_space_flag(data)))
			return (0);
	if ((id = has_flag("+", data->flags)) >= 0)
		if (!(generic_plus_flag(data)))
			return (0);
	if ((id = has_flag("-", data->flags)) >= 0)
		if (!(generic_minus_flag(data, id)))
			return (0);
	if ((id = has_flag("0", data->flags)) >= 0)
		if (!(generic_zero_flag(data, id)))
			return (0);
	if (data->value_format == NULL)
		if ((data->value_format = ft_strdup(data->value)) == NULL)
			return (0);
	return (1);
}

int			convert_double(t_data *data)
{
	char *tmp;

	tmp = NULL;
	if (data->precision == NULL)
		if (!(data->precision = ft_strdup("6")))
			return (0);
	if (!ft_strequ(data->value, "inf") && !ft_strequ(data->value, "-inf")
		&& !ft_strequ(data->value, "nan") && !ft_strequ(data->value, "-nan")
		&& !ft_strequ(data->value, "0"))
	{
		if (data->precision != NULL && !(precision(data)))
			return (0);
		if (ft_strequ(data->precision, "0") && has_flag("#", data->flags) < 0)
		{
			tmp = data->value_format;
			data->value_format = ft_strremove(tmp, ft_strclen(tmp, '.'), 1);
			ft_strdel(&tmp);
		}
	}
	if (!(flags(data)))
		return (0);
	if (data->min_field_width != NULL)
		if (!(min_field_width(data)))
			return (0);
	return (1);
}
