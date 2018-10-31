/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 14:49:41 by rlucas-d          #+#    #+#             */
/*   Updated: 2018/10/31 23:01:28 by rlucas-d         ###   ########.fr       */
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
		printf("GNL--%s\n", line);
		free(line);
		printf("-------------\n");
	}
	close(fd);
	while (19)
		;
}
