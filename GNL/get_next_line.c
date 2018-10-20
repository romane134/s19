/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 17:31:26 by rlucas-d          #+#    #+#             */
/*   Updated: 2018/10/17 08:23:12 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static int		ft_checkstop(static char buf)
{
	int a;

	while (buf[a])
	{
		if (buf[a] == '\n')
			return (1);
		buf[a++];
	}
	return (0);
}

char			*ft_stock_buf(char **str, static char *buf)
{
	int a;
	int b;
	char *stock;

	b = 0;
	str[a] = ft_read();

	if (a = ft_strchr(buf, '\n')) //on est au premier '\n'?
		while (a < BUFF_SIZE)
			str[a++] = stock[b++];
	if (buf[BUFF_SIZE] == '\0')
			ft_strcpy(str, stock);
	return (stock);
}
static char		*ft_read(static  char *buf, const int fd, char **str)
{
	int ret;
	static char		buf[BUFF_SIZE + 1];
	char *tmp;
	while (BUFF_SIZE > 0)
	{
		if (str = ft_stock_buf)
	}
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0) // ecrase le text de la lecture precedente
	{
		buf[ret] = '\0';
		if (!(ft_strchr(buf, '\n')))
		{
			tmp = *str;
			*str = ft_strjoin(*str, buf); //faire une fonction pour moove ces 3 lignes de merde (☞ﾟヮﾟ)☞
			free(tmp);
			return (&str);
		}
		if (tmp = ft_strchr(buf, '\n'))
		{
			*tmp = 0;
			tmp = *str;
			*str = ft_strjoin(*str, buf); //ici, mettre une fonction qui sotck le reste du buffer
			free(tmp);
		//	tmp = ft_strchr(buf, '\0');
		//	*tmp = '\n';
		*str = ft_stock(*str, buf /*....*/)
			return (&str)
		}
	}
	if (ret == 0)
		return (0);
}

int		get_next_line(const int fd, char **line)
{
	int			ret;
	char		**str;
	static char	*buf;

	if (fd < 0 || !line || BUFF_SIZE <= 0)
		return (-1);
	*line = str;
	if ('\n' |||| *str = ft_read(buf, fd, &str)) //j'ai lu jusq '\n'      &str difg
	{
 		//finir
	}

	if (ft_read(buf ,fd, &str) == 0) //pas appeller ft_stock_buff plutot??
		return (0);

	return (0);
}
