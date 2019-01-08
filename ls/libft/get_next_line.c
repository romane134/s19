/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smondesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 14:52:57 by smondesi          #+#    #+#             */
/*   Updated: 2018/12/07 14:23:02 by smondesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		return_number(int ret, char *tmp, char **line, char *mem)
{
	if (ret < 0)
	{
		if (mem != NULL)
			free(mem);
		free(tmp);
		return (-1);
	}
	if (ret == 0 && (tmp[0] == '\0'))
	{
		free(tmp);
		return (0);
	}
	*line = ft_strnew(ft_strlen(tmp));
	ft_strcpy(*line, tmp);
	free(tmp);
	return (1);
}

int		join_tmp(char **tmp, char *s1)
{
	char *s;

	s = *tmp;
	if (!(*tmp = ft_strjoin(s, s1)))
		return (-1);
	free(s);
	return (1);
}

int		copy(char *str, char **tmp)
{
	int		i;
	char	*s;

	i = 0;
	while (str[i] != '\n')
		i++;
	if (!(s = ft_strnew(i)))
		return (-1);
	ft_strncpy(s, str, i);
	join_tmp(tmp, s);
	free(s);
	return (i);
}

int		read_that(const int fd, char *tmp, char **mem, char **line)
{
	char	buf[BUFF_SIZE + 1];
	int		var[2];

	while ((var[0] = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[var[0]] = 0;
		if (ft_strchr(buf, '\n'))
		{
			if ((var[1] = copy(buf, &tmp)) == -1 ||
					(!(mem[fd] = ft_strnew(var[0] - (var[1] + 1)))))
				return (return_number(-1, tmp, line, mem[fd]));
			free(mem[fd]);
			mem[fd] = ft_strsub(buf, var[1] + 1, (var[0] - (var[1] + 1)));
			break ;
		}
		else
		{
			if ((join_tmp(&tmp, buf)) == -1)
				return (return_number(-1, tmp, line, mem[fd]));
		}
	}
	return (return_number(var[0], tmp, line, mem[fd]));
}

int		get_next_line(const int fd, char **line)
{
	static char		*mem[OPEN_MAX];
	char			*tmp[2];
	int				i;

	if (fd < 0 || fd > OPEN_MAX || (!(tmp[0] = ft_strnew(0))))
		return (-1);
	if (mem[fd] != NULL)
	{
		if (ft_strchr(mem[fd], '\n'))
		{
			if ((i = copy(mem[fd], &tmp[0])) == -1)
				return (return_number(-1, tmp[0], line, mem[fd]));
			tmp[1] = mem[fd];
			mem[fd] = ft_strsub(tmp[1], i + 1, (ft_strlen(tmp[1]) - (i + 1)));
			free(tmp[1]);
			return ((return_number(1, tmp[0], line, mem[fd])));
		}
		else
		{
			if (join_tmp(&tmp[0], mem[fd]) == -1)
				return (return_number(-1, tmp[0], line, mem[fd]));
			ft_strdel(&mem[fd]);
		}
	}
	return (read_that(fd, tmp[0], mem, line));
}
