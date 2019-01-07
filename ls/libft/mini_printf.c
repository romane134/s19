/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smondesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 13:28:29 by smondesi          #+#    #+#             */
/*   Updated: 2018/12/17 12:15:03 by smondesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libft.h"
#include <stdio.h>

void		ft_lil_x(char *s)
{
	while (*s)
	{
		if (ft_isalpha(*s) == 1)
			*s = *s + 32;
		ft_putchar(*s);
		s++;
	}
}

const char	*ft_which_one(const char *fmt, void *ap)
{
	if (*fmt == '+')
	{
		while (*fmt == '+')
			fmt++;
		if ((*fmt == 'd' || *fmt == 'i') && ap > 0)
			ft_putchar('+');
	}
	if (*fmt == 's')
		ft_putstr((char *)ap);
	else if (*fmt == 'd' || *fmt == 'i')
		ft_putnbr((int)ap);
	else if (*fmt == 'c')
		ft_putchar((char)ap);
	else if (*fmt == 'o')
		ft_putstr(st_itoa_base((int)ap, 8));
	else if (*fmt == 'X')
		ft_putstr(st_itoa_base((int)ap, 16));
	else if (*fmt == 'x')
		ft_lil_x(st_itoa_base((int)ap, 16));
	return (fmt);
}

int			st_printf(const char *restrict fmt, ...)
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
				ft_putchar('%');
			else
			{
				c = va_arg(ap, void *);
				fmt = ft_which_one(fmt, c);
			}
		}
		else
			ft_putchar(*fmt);
		fmt++;
	}
	va_end(ap);
	return (0);
}
