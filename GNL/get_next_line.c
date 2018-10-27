/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 17:31:26 by rlucas-d          #+#    #+#             */
/*   Updated: 2018/10/27 17:42:23 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*ft_check_rest(char *rest)
{
	int		i;

	i = 0;
	if (ft_strchr(rest, '\n'))
	{
		while (rest[i] != '\n')
			i++;
		rest[i] = '\0';
		return (rest);
	}
	return (rest);
}

char	*ft_read_line(char *buf, const int fd)
{
	int				ret;
	char			*str;
	char			*tmp;
	static char		*rest;
	int				i;

	if (rest == NULL)
		rest = ft_strnew(0);
	if (*rest)
	{
		rest = ft_check_rest(rest);
		if (ft_strchr(rest, '\n'))
		{
			return (rest - 1);
		}
		str = rest;
	}
	else
		str = ft_strnew(0);
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		tmp = str;
		str = ft_strjoin(str, buf);
		free(tmp);
		if ((ft_strchr(buf, '\n')))
			break ;
	}
	if (str[ret - 1] == '\n')
	{
		str[ft_strlen(str) - 1] = '\0';
		return (str);
	}
	else
	{
		i = 0;
		while (str[i] != '\n' && str[i])
			i++;
		str[i] = '\0';
		rest = ft_strdup(str + i + 1);
		return (str);
	}
	if (ret == -1)
		return (NULL);
	return (str);
}

int		get_next_line(const int fd, char **line)
{
	char	buf[BUFF_SIZE + 1];

	if (fd < 0 || !line || BUFF_SIZE <= 0)
		return (-1);
	if (!(*line = ft_read_line(buf, fd)))
	{
		free(ft_read_line(buf, fd));
		return (-1);
	}
	if (**line == 0)
		return (0);
	return (1);
}

#include <stdio.h>
#include <fcntl.h>

int		main(void)
{
	int		fd;
	char	*line;

	fd = open("file.txt", O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		printf("GNL--%s\n", line);
		free(line);
		printf("!!!!!!!!!!!!!!!!\n");
	}
	close(fd);
}
