/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_printf_error.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 14:53:14 by rlucas-d          #+#    #+#             */
/*   Updated: 2019/02/10 11:19:30 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libft.h"
#include <stdio.h>

static void				ft_putchar_error(char c)
{
	write(2, &c, 1);
}

static void				ft_putstr_error(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		ft_putchar_error(str[i]);
		i++;
	}
}

static void				ft_lil_x(char *s)
{
	while (*s)
	{
		if (ft_isalpha(*s) == 1)
			*s = *s + 32;
		ft_putchar_error(*s);
		s++;
	}
}

static const char		*ft_which_one(const char *fmt, void *ap)
{
	if (*fmt == '+')
	{
		while (*fmt == '+')
			fmt++;
		if ((*fmt == 'd' || *fmt == 'i') && ap > 0)
			ft_putchar_error('+');
	}
	if (*fmt == 's')
		ft_putstr_error((char *)ap);
	else if (*fmt == 'd' || *fmt == 'i')
		ft_putnbr_fd((int)ap, 2);
	else if (*fmt == 'c')
		ft_putchar_error((char)ap);
	else if (*fmt == 'o')
		ft_putstr_error(st_itoa_base((int)ap, 8));
	else if (*fmt == 'X')
		ft_putstr_error(st_itoa_base((int)ap, 16));
	else if (*fmt == 'x')
		ft_lil_x(st_itoa_base((int)ap, 16));
	return (fmt);
}

int						st_printf_error(const char *restrict fmt, ...)
{
	va_list	ap;
	void	*c;

	va_start(ap, fmt);
	while (*fmt != '\0')
	{
		if (*fmt == '%')
		{
			fmt++;
			if (*fmt == '%')
				ft_putchar_error('%');
			else
			{
				c = va_arg(ap, void *);
				fmt = ft_which_one(fmt, c);
			}
		}
		else
			ft_putchar_error(*fmt);
		fmt++;
	}
	va_end(ap);
	return (0);
}
