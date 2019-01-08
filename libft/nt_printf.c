/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nt_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 11:46:27 by rlucas-d          #+#    #+#             */
/*   Updated: 2018/12/05 10:40:47 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>
#include <stdio.h>

int		ft_choose(char *format, va_list ap, int i)
{
	if (format[i] == 'd' || format[i] == 'i')
		ft_putstr(ft_itoa(va_arg(ap, int)));
	else if (format[i] == 'c')
		ft_putchar(va_arg(ap, int));
	else if (format[i] == 's')
		ft_putstr(va_arg(ap, char*));
	else if (format[i] == '%')
		ft_putchar('%');
	return (0);
}

int		nt_printf(const char *restrict format, ...)
{
	va_list	ap;
	int		i;

	i = 0;
	va_start(ap, format);
	while (format[i] != '\0')
	{
		if (format[i + 1] != '%')
			ft_putchar(format[i]);
		else
			i++;
		if (format[i] == '%')
		{
			i++;
			ft_choose((char *)format, ap, i);
		}
		i++;
	}
	return (0);
}
