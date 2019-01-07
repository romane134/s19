/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_stat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smondesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 12:14:31 by smondesi          #+#    #+#             */
/*   Updated: 2018/12/10 12:25:42 by smondesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <sys/stat.h>

int		main(int argc, char **argv)
{
	char *fd = argv[1];
	struct stat *buf;

	buf = (struct stat *)malloc(sizeof(struct stat));

	stat(fd, buf);
	printf("%hu", buf->st_mode);
	free (buf);
}
