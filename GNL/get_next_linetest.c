/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 17:31:26 by rlucas-d          #+#    #+#             */
/*   Updated: 2018/10/21 19:46:47 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*ft_stock_buf(char *buf, int fd)
{

}

int		ft_check_buf(char *buf, int ret)
{
	if (buf[ret] == '\n')
		return (1);
	else
	{
		
	}
}

char	*ft_read_line(char *buf, const int fd)
{
	int		ret;
	char	*str;
	char	buff[BUFF_SIZE + 1];
	char	*tmp;
	char	*rest;

	str = ft_strnew(0);
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf = ft_strjoin(rest, buf);
		buf[ret] = '\0';
		if (!(ft_strchr(buf, '\n')))
		{
			tmp = str;
			str = ft_strjoin(str, buf);
			free(tmp);
		}
		else
		{
			if (ft_stock_rest(buf, ret) != 0)
			{
				tmp = str;
				str = ft_strjoin(str, buf);
				free(tmp);
				return (str);
			}
			else
			{
				str = 
				 = ft_stock_buf(buf, ret, str, tmp);
			}
		}
	}
	if (ret == -1)
		return (NULL);
	return (str);
}

int			get_next_line(const int fd, char **line)
{
	char 	*tmp;
	char	*buf;

	if (fd < 0 || !line || BUFF_SIZE <= 0)
		return (-1);
	if (!(*line = ft_read_line(buf, fd)))
		return (-1);
	if (**line == 0)
		return (0);
	return (1);
}
