/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 17:31:26 by rlucas-d          #+#    #+#             */
/*   Updated: 2018/10/22 12:37:59 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>


int		ft_check_buf(char *buf, int ret)
{
	if (buf[ret] == '\n')
		return (1);
	return (0);
}

char	*ft_read_line(char *buf, const int fd)
{
	int				ret;
	char			*str;
	char			*tmp;
	static char		*rest; //la premiere fois le rest == NULL non? donc que faire?

	rest = NULL;
	str = ft_strnew(0); //je dois free str non??
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		if (rest == NULL)
			rest = ft_strnew(0);
		buf = ft_strjoin(rest, buf);
		buf[ret] = '\0';

		if (!(ft_strchr(buf, '\n'))) //ici on a pas de \n donc on relit encore la prochaine fois vu que pas de return
		{
			tmp = str;
			str = ft_strjoin(str, buf);
			free(tmp);
		}
		else
		{
			if (ft_check_buf(buf, ret) != 0) //ici on a un \n et il est a la fin du buf donc on peut return
			{
				tmp = str;
				str = ft_strjoin(str, buf);
				free(tmp);
				return (str); //on return la ligne
			}
			else // on a un \n mais il y a autre chose apres
			{
				while (*str != '\n')
					str++;
				rest = ft_strncpy(rest, str, (ret - *str)); // on copie a partir du \n (la ou pointe str?) jusqu'a la fin de ret
				return (str);
			}
		}
	}
	if (ret == -1)
		return (NULL);
	return (str);
}

int			get_next_line(const int fd, char **line)
{
	char		buf[BUFF_SIZE + 1];

	if (fd < 0 || !line || BUFF_SIZE <= 0)
		return (-1);
	if (!(*line = ft_read_line(buf, fd)))
		return (-1);
	if (**line == 0)
		return (0);
	return (1);
}
