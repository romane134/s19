/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   T_2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smondesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 14:33:09 by smondesi          #+#    #+#             */
/*   Updated: 2018/12/17 13:31:46 by smondesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include "libft/libft.h"
#include <time.h>
#include <pwd.h>

void	flag_l(char *t, struct stat *buf)
{
	printf("fd");
}

void	lecture(char *flag, char *doc)
{
	DIR				*dirp;
	struct dirent	*dp;
	char			**fludg;

	dirp = opendir(doc);
	while ((dp = readdir(dirp)) != NULL)
	{
		if (dp->d_name[0] != '.' || ft_strchr(flag, 'a') != NULL)
		{
			st_printf("%s\n", dp->d_name);
		}
	}
	closedir(dirp);
}

void	which_flag(char **argv, int argc)
{
	int		i;
	char	*flag;

	i = 1;
	flag = ft_strnew(0);
	while (i < argc && argv[i][0] == '-')
	{
		flag = ft_strjoin(flag, argv[i]);
		i++;
	}
	if (i == argc)
		lecture(flag, ".");
	else
		while (i < argc)
		{
			lecture(flag, argv[i]);
			i++;
		}
}

int		main(int argc, char **argv)
{
	which_flag(argv, argc);
}
