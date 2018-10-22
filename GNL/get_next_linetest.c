/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 17:31:26 by rlucas-d          #+#    #+#             */
/*   Updated: 2018/10/22 18:43:45 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int		ft_check_buf(char *str, int ret)
{
	if (str[ret - 1] == '\n')
		return (1);
	return (0);
}

char	*ft_read_line(char *buf, const int fd)
{
	int				ret;
	char			*str;
	char			*tmp;
	static char		*rest;
	int				i;

	i = 0;
	if (rest == NULL)
		rest = ft_strnew(0);
	printf("rest2 = %s\n",rest);
	str = ft_strnew(0); /*je dois free str non??*/
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		printf("rest3 ---%s\n", rest);
		printf("buf-----%s\n", buf);
		buf = ft_strjoin(rest, buf);
		printf("buf join--- = %s\n", buf);	

		if (!(ft_strchr(buf, '\n')))/* ici on a pas de \n donc on relit encore la prochaine fois vu que pas de return */
		{

			tmp = str;
			str = ft_strjoin(str, buf);
			free(tmp);
		}
		else
		{
			tmp = str;
			str = ft_strjoin(str, buf);
			free(tmp);

			if (ft_check_buf(str, ft_strlen(str)) != 0)/*ici on a un \n et il est a la fin du buf donc on peut return*/
			{

				str[ft_strlen(str) - 1] = '\0';
				return (str);/*on return la ligne*/
			}
			else/*on a un \n mais il y a autre chose apres*/
			{
				while (str[i] != '\n')
					i++;
				str[i] = '\0';
				rest = ft_strdup(str + i + 1);
				//printf("rest = %s\n",rest);	
				return (str);
			}
		}
	}
	if (ret == -1)
		return (NULL);
	return (str);
}

int		get_next_line(const int fd, char **line)
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

#include <stdio.h>
#include <fcntl.h>

int		main(void)
{
	int		fd;
	char	*line;

	fd = open("file.txt", O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		printf("%s\n", line);
		free(line);
		printf("!!!!!!!!!!!!!!!!\n");
	}
	close(fd);
}
