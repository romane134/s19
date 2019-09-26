/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/02 18:11:46 by vjovanov          #+#    #+#             */
/*   Updated: 2018/11/21 23:24:44 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/*
** NAME:
** 	ft_printf
**
** DESCRIPTION:
**	ft_print() affiche a l'ecran la chaine de caractere 'format' avec les
**	differents parametres recus.
**
** SYNOPSIS:
**	int ft_printf(const char *format, ...)
**
** PARAMS:
** 	format - La chaine de caractere a formater
**	... - parametres permettant le formatage de la chaine de caractere
**
** RETURN VALUE:
**	(int) le nombre de caractere ecrits. Si une erreur est survenue,
**	retourne une valeur negative.
**
** steps[0] = flags
** steps[1] = min_field_width
** steps[2] = precision
** steps[3] = conversion_flags
*/

static int	print_result(t_data *data)
{
	int length;
	int id;
	int i;

	length = 1;
	i = -1;
	if (data->min_field_width != NULL)
		length = ft_atoi(data->min_field_width);
	else if ((id = has_flag("-", data->flags)) >= 0)
		length = ft_atoi(&(data->flags[id][1]));
	length = (length == 0) ? 1 : length;
	if (data->identifier == 'c' && data->value[0] == 0)
	{
		if (data->min_field_width == NULL)
			while (++i < length)
				ft_putchar(data->value_format[length - i - 1]);
		else
			while (++i < length)
				ft_putchar(data->value_format[i]);
	}
	else
		ft_putstr(data->value_format);
	return (data->identifier == 'c' && data->value[0] == 0 ? i :
		ft_strlen(data->value_format));
}

int			read_percent(const char *format, va_list ap, t_data *data, int *i)
{
	int	bytes;

	bytes = 0;
	if (!(formatting(format, data, ap)))
	{
		free_data(data);
		return (-1);
	}
	bytes = print_result(data);
	*i += (int)ft_strlen(data->s_fmt_orig) - 1;
	free_data(data);
	return (bytes);
}

int			read_color(const char *format, int *i)
{
	char	*color;
	int		bytes;

	bytes = 0;
	if (!(color = coloring(format)))
	{
		ft_putchar(format[0]);
		bytes++;
		return (bytes);
	}
	ft_putstr(color);
	bytes = (int)ft_strlen(color);
	*i += (int)ft_strclen(format, '}');
	return (bytes);
}

int			read_format(const char *format, t_data *data, va_list ap, int *i)
{
	int bytes;

	bytes = 0;
	if (format[0] == '%')
		bytes = read_percent(format, ap, data, i);
	else if (format[0] == '{')
		bytes += read_color(format, i);
	else
	{
		bytes++;
		ft_putchar(format[0]);
	}
	return (bytes);
}

int			ft_printf(const char *format, ...)
{
	va_list ap;
	t_data	data;
	int		i;
	int		bytes;
	int		ret;

	if (format == NULL)
		return (0);
	i = -1;
	bytes = 0;
	ret = 0;
	set_data(&data);
	va_start(ap, format);
	while (format[++i])
	{
		if ((ret = read_format(&(format[i]), &data, ap, &i)) == -1)
			return (0);
		bytes += ret;
	}
	va_end(ap);
	return (bytes);
}
