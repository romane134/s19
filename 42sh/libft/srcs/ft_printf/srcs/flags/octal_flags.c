/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   octal_flags.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 17:51:50 by vjovanov          #+#    #+#             */
/*   Updated: 2018/11/20 17:51:51 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

int		octal_hashtag_flag(t_data *data)
{
	char *tmp;

	tmp = NULL;
	if ((tmp = ft_strjoin("0", data->value_format)) == NULL)
		return (0);
	ft_strdel(&(data->value_format));
	if (!(data->value_format = ft_strdup(tmp)))
		return (!del_array(tmp));
	ft_strdel(&tmp);
	return (1);
}
