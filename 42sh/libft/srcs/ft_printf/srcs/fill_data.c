/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 13:47:31 by vjovanov          #+#    #+#             */
/*   Updated: 2018/11/21 22:46:49 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char		*fill_conv_flags(char *s_fmt, int ret)
{
	char	*res;

	res = NULL;
	if ((res = ft_strsub(s_fmt, 0, ret)) == NULL)
		return (NULL);
	return (res);
}

char		*fill_precision(char *s_fmt, va_list ap, int ret)
{
	int		star;
	char	*res;

	star = 0;
	res = NULL;
	if (ret == 1)
	{
		if ((res = ft_strdup("0")) == NULL)
			return (NULL);
		return (res);
	}
	if (s_fmt[ret - 1] == '*')
	{
		star = (int)va_arg(ap, int);
		if ((res = ft_itoa(star)) == NULL)
			return (NULL);
		return (res);
	}
	if ((res = ft_strsub(s_fmt, 1, ret - 1)) == NULL)
		return (NULL);
	return (res);
}

char		*fill_field_width(char *s_fmt, va_list ap, int ret)
{
	int		star;
	char	*res;

	star = 0;
	res = NULL;
	if (*s_fmt == '*')
	{
		star = (int)va_arg(ap, int);
		if ((res = ft_itoa(star)) == NULL)
			return (NULL);
		return (res);
	}
	if ((res = ft_strsub(s_fmt, 0, ret)) == NULL)
		return (NULL);
	return (res);
}

char		*fill_flags(char *s_fmt, va_list ap, int ret)
{
	int		star;
	char	*res;
	char	*tmp1;
	char	*tmp2;

	star = 0;
	res = NULL;
	if (s_fmt[ret - 1] == '*')
	{
		star = (int)va_arg(ap, int);
		tmp1 = ft_strsub(s_fmt, 0, 1);
		tmp2 = ft_itoa(star);
		res = ft_strjoin(tmp1, tmp2);
		ft_memdel((void**)&tmp1);
		ft_memdel((void**)&tmp2);
		if (res == NULL)
			return (NULL);
		return (res);
	}
	if ((res = ft_strsub(s_fmt, 0, ret)) == NULL)
		return (NULL);
	return (res);
}

char		fill_id(char *s_fmt)
{
	char id;

	id = s_fmt[0];
	return (id);
}
