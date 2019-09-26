/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_flags.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 12:34:07 by vjovanov          #+#    #+#             */
/*   Updated: 2018/12/12 12:34:08 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

int			binary_hashtag_flag(t_data *data)
{
	int		i;
	char	*tmp;
	long	size;

	if ((size = set_size_binary(data)) == 0)
		return (0);
	if ((tmp = ft_strnew(size)) == NULL)
		return (0);
	i = (data->value_format[0] == '-') ? 1 : 0;
	ft_memset(tmp, '0', size);
	ft_strcpy(&(tmp[size - ft_strlen(&(data->value_format[i]))]),
		&(data->value_format[i]));
	ft_strdel(&data->value_format);
	if (!(data->value_format = ft_strdup(tmp)))
	{
		ft_strdel(&tmp);
		return (0);
	}
	if (ft_atoll(data->value) >= 0)
		return (1);
	convert_two_complement(data);
	return (del_array(tmp));
}
