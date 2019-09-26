/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 23:02:41 by vjovanov          #+#    #+#             */
/*   Updated: 2018/11/21 22:19:45 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		dispatcher(t_data *data, va_list ap)
{
	int i;

	i = 0;
	while (data->identifier != get_identifiers()[i].identifier)
		i++;
	if (ft_strequ(get_identifiers()[i].value_type, "int"))
		set_int(data, ap);
	else if (ft_strequ(get_identifiers()[i].value_type, "unsigned int"))
		set_unsigned_int(data, ap);
	else if (ft_strequ(get_identifiers()[i].value_type, "char"))
		set_char(data, ap);
	else if (ft_strequ(get_identifiers()[i].value_type, "string"))
		set_string(data, ap);
	else if (ft_strequ(get_identifiers()[i].value_type, "void*"))
		data->value = ft_ulltoa((unsigned long long)va_arg(
			ap, unsigned long long));
	else if (ft_strequ(get_identifiers()[i].value_type, "double"))
		set_double(data, ap);
	else if (ft_strequ(get_identifiers()[i].value_type, "nothing"))
		data->value = ft_strdup(&(get_identifiers()[i].identifier));
	if (data->value == NULL)
		return (0);
	return (get_identifiers()[i].f(data));
}
