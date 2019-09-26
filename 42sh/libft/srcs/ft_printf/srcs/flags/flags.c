/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 15:28:14 by vjovanov          #+#    #+#             */
/*   Updated: 2018/11/19 19:24:34 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

int				has_flag(char *flag, char **flags)
{
	int i;

	i = 0;
	while (flags[i])
	{
		if (flags[i][0] == flag[0])
			return (i);
		i++;
	}
	return (-1);
}

int				is_acceparrayle_flag(char identifier, char flag)
{
	int i;
	int j;

	i = 0;
	while (get_identifiers()[i].identifier != identifier)
		i++;
	j = 0;
	while (j < ft_array_length((void**)get_identifiers()[i].accepted_flags))
	{
		if (get_identifiers()[i].accepted_flags[j][0] == flag)
			return (1);
		j++;
	}
	return (0);
}

int				is_acceparrayle_conv_flag(char identifier, char *flag, int len)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (get_identifiers()[i].identifier != identifier)
		i++;
	while (j < ft_array_length(
		(void**)get_identifiers()[i].accepted_conversion_flag))
	{
		if (ft_strnequ(get_identifiers()[i].accepted_conversion_flag[j],
			flag, len))
			return (1);
		j++;
	}
	return (0);
}
