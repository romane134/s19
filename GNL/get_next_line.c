/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 17:31:26 by rlucas-d          #+#    #+#             */
/*   Updated: 2018/10/29 19:38:02 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
char	*ft_line(char *str, char **rest)
{
	int		i;

//	if (str[ft_strlen(*rest) - 1] == '\n')
//	{
//		if (ft_strlen(rest) == 1)
//			return (str);
//		str[ft_strlen(rest) - 1] = '\0';
//		return (str);
//	}
//	else
//	{
		i = 0;
		while (str[i] != '\n' && str[i])
			i++;
		if (str[i] != '\0')
			*rest = ft_strdup(str + i + 1);
		str[i] = '\0';
		return (str);
//	}
}

char	*ft_read(char *buf, const int fd)
{
	int				ret;
	char			*tmp;
	char			*str;
	static char		*rest[OPEN_MAX];

	if (rest[fd] == NULL)
		rest[fd] = ft_strnew(0);
	str = ft_strdup(rest[fd]);
	rest[fd] = ft_strnew(0);
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		tmp = str;
		str = ft_strjoin(str, buf);
		free(tmp);
		if ((ft_strchr(buf, '\n')))
			break ;
	}
	str = ft_line(str, &(rest[fd]));
	if (ret == -1)
		return (NULL);
	return (str);
}

int		get_next_line(const int fd, char **line)
{
	char	buf[BUFF_SIZE + 1];

	if (fd < 0 || !line || BUFF_SIZE <= 0 || fd > OPEN_MAX)
		return (-1);
	if (!(*line = ft_read(buf, fd)))
		return (-1);
	if (**line == '\n')
	{
		**line = '\0';
		return (1);
	}
	if (**line == 0)
		return (0);
	return (1);
}
