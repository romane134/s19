/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   T_2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smondesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 14:33:09 by smondesi          #+#    #+#             */
/*   Updated: 2019/01/04 16:14:03 by smondesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include "../libft/libft.h"
#include "../includes/ft_ls.h"
#include <time.h>
#include <pwd.h>

int		can_rec(char *flag, char *doc)
{
	struct stat *buf;

	buf = (struct stat *)malloc(sizeof(struct stat));
	stat(doc, buf);
	if (buf->st_mode == 16877 && ft_strchr(flag, 'R') != NULL)
		return (1);
	return (0);
}

void	lecture(char *flag, char *doc)
{
	DIR				*dirp;
	struct dirent	*dp;
	char			*fludg;

	dirp = opendir(doc);
	doc = ft_strjoin(doc, "/");
	while ((dp = readdir(dirp)) != NULL)
	{
		if (dp->d_name[0] != '.' || ft_strchr(flag, 'a') != NULL)
		{
			fludg = ft_strjoin(doc, dp->d_name);
			if (ft_strchr(flag, 'l'))
				analyse_file(fludg);
			st_printf("%s\n", dp->d_name);
			if (can_rec(flag, fludg) == 1)
			{
				if (ft_strcmp(dp->d_name, ".") != 0 &&
						ft_strcmp(dp->d_name, "..") != 0)
					lecture(flag, fludg);
				st_printf("\n");
			}
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
