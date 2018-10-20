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
#include "libft.h"
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

char			*ft_stock_buf(char **str, static char *buf, const int fd)
{
	int ret;
	int b;
	char *stock;
	static char		buf[BUFF_SIZE + 1];

	b = 0;
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		if (str[ret] = ft_strchr(buf, '\n'))
		{
			ft_strncpy(str, stock, (size_t)a); //souuuuucis aaaah, peut etre paaaas
		}
		if (buf[BUFF_SIZE] == '\0')
				ft_strcpy(str, stock)
			return (stock);
	}
	if (ret == 0)
		return (0);
}
static char		*ft_check_line(static  char *buf, const int fd, char **str)
{
	char *tmp;
	*str = ft_stock_buf();
	if (ft_strchr(*str, '\n'))
	{

		return (1)
	}
	else
	{
		ft_strjoin(str, buf/*???*/)
	}


}

int		get_next_line(const int fd, char **line)
{
	int			ret;
	char		**str;
	static char	*buf;

	if (fd < 0 || !line || BUFF_SIZE <= 0)
		return (-1);
	*line = str;
	if (ft_stock(buf, fd, &str))
	{
		if (ft_check_line == 1)
		*line = *str;
		free (str)

	}

	if (ft_read(buf ,fd, &str) == 0) //pas appeller ft_stock plutot??
		return (0);

	return (0);
}
