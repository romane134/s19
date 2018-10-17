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

int				ft_clear_buf(static char *buf, /*...*/)
{
	int a;

	a = ft_strchr(buf, '\n'); //on est au premier '\n'?
	while (buf[a++])
		if (ft_strchr(buf, '\n') == 0)
			return (0);
	return (1);
}
static char		*ft_read(static  char *buf, const int fd, char **str)
{
	int ret;
	static char		buf[BUFF_SIZE + 1];
	char *tmp;
	while (BUFF_SIZE > 0)
	{
		if (ft_clear_buf(buf,/*...*/ ) == 1); //on a un autre '\n'
		{

		}
		// fonction qui si jamais on trouve un autre '\n dans le buffsize qui reste va le return (1) en strjoin le *str //sinon suave dans le buf et go read avec un join dans ce qu'on a deja 
		else
			*str = ft_strjoin(*str, buf); //sauver ce qu'il restait dans le buf avant de reafaire un read (ok mais on ecrase jamais ce qu'il a dessus....)
		// on est |e| '\n' et '\0' go go go modifier ici pour pas perdre de text
		
	}
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0) // ecrase le text de la lecture precedente 
	{
		buf[ret] = '\0';
		if (!(ft_strchr(buf, '\n')))
		{
			tmp = *str;
			*str = ft_strjoin(*str, buf); //faire une fonction pour moove ces 3 lignes de merde (☞ﾟヮﾟ)☞
			free(tmp);
		}
		if (tmp = ft_strchr(buf, '\n'))
		{
			*tmp = 0;
			tmp = *str;
			*str = ft_strjoin(*str, buf); //soucis : si on stop mtn, au prochain read, on perdra une partie du text (|e| '\n' et '\0')
			free(tmp);
			tmp = ft_strchr(buf, '\0');
			*tmp = '\n';
			return (1)
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
	if ('\n ||||| *str = ft_read(buf, fd, &str)) //j'ai lu jusq '\n'      &str difg
	{
		*line = &str;  //finir
	}

	if (ft_read(buf ,fd, &str) == 0)
		return (0);

	return (0);
}
