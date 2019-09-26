/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_pointer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 16:19:04 by vjovanov          #+#    #+#             */
/*   Updated: 2018/11/19 15:25:33 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

static int	flags(t_data *data)
{
	int	id;

	if ((id = has_flag("-", data->flags)) >= 0)
		if (!(generic_minus_flag(data, id)))
			return (0);
	return (1);
}

int			convert_pointer(t_data *data)
{
	char *nb;

	if (!(nb = ft_ulltoa_base(ft_atoull(data->value), 16)))
		return (0);
	if (!(data->value_format = ft_strjoin("0x", nb)))
	{
		ft_strdel(&nb);
		return (0);
	}
	ft_strdel(&nb);
	if (!(flags(data)))
		return (0);
	if (data->min_field_width != NULL)
		if (!(min_field_width(data)))
			return (0);
	return (1);
}
