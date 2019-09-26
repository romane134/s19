/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 20:15:49 by vjovanov          #+#    #+#             */
/*   Updated: 2018/12/11 20:15:50 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		del_array(char *tmp)
{
	ft_strdel(&tmp);
	return (1);
}

int		formatting(const char *format, t_data *data, va_list ap)
{
	int		i;
	char	*sub;
	char	*tmp;

	tmp = NULL;
	i = 1;
	while (!is_identifier(format[i]) && format[i])
		i++;
	if ((sub = ft_strsub(format, 1, i)) == NULL ||
		(data->s_fmt_orig = ft_strjoin("%", sub)) == NULL)
		return (!del_array(sub));
	if (format[i] != '\0' && (tmp = check_sub((const char*)sub)) != NULL)
	{
		if ((data->s_fmt_new = ft_strjoin("%", tmp)) == NULL)
			return (0);
		ft_strdel(&tmp);
		if (!(check_new_sub(data->s_fmt_new)))
			return (0);
		if (!(fill_data(data, ap)))
			return (0);
	}
	else if (del_array(sub) &&
		!(data->value_format = ft_strdup(data->s_fmt_orig)))
		return (0);
	return (1);
}

char	*coloring(const char *format)
{
	int i;
	int j;

	j = 0;
	i = 1;
	while (format[i] != '}' && format[i])
		i++;
	if (format[i] == '\0')
		return (NULL);
	while (j < NB_COLORS)
	{
		if (ft_strnequ(&(format[1]), get_colors()[j].name, i - 1))
			return (get_colors()[j].code);
		j++;
	}
	return (NULL);
}
