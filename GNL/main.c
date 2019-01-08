/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 14:49:41 by rlucas-d          #+#    #+#             */
/*   Updated: 2018/11/06 16:37:50 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

int		main(void)
{
	int		fd;
	char	*line;

	line = NULL;
	fd = open("file.txt", O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		printf("%s", line);
		free(line);
	}
	while (19)
		;
	close(fd);
}
