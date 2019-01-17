/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 13:38:41 by rlucas-d          #+#    #+#             */
/*   Updated: 2019/01/16 13:57:51 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void		lecture(int flag, char *doc)
{
	DIR				*dirp;
	struct dirent	*dp;
	char			*fludg;
	t_file			file;

	if (!(dirp = opendir(doc)))
	{
		st_printf("ls: %s\n", strerror(errno));
		exit(0);
	}
	doc = ft_strjoin(doc, "/");
	while ((dp = readdir(dirp)) != NULL)
	{
		fludg = ft_strjoin(doc, dp->d_name);
		file.name = dp->d_name;
		//(((flag & A_FLAG) != 0)
		if (((flag & L_FLAG) == L_FLAG))
			print_info_file(fludg, file);
		//	lecture(flag, fludg);
		//st_printf("\n");
		st_printf("%s\n", file.name);
	}
	closedir(dirp);
}

void		ft_what_kind(char *flag, char *doc)
{
	struct stat	s;
	t_file		file;

	(void)flag;
	if ((stat(doc, &s) == -1))
	{
		st_printf("stat: %s\n", strerror(errno));
	}
	if (!(opendir(doc)))
	{
		file.name = doc;
	}
}

int			main(int argc, char **argv)
{
	int		flag;
	int		i;

	(void)argc;
	flag = 0;
	i = ft_flag(argv, &flag);
	if (i > argc)
		lecture(flag, ".");
	else
	{
		if (!(what_kind(flag, argv[i])))
			printf ("error");
		lecture(flag, argv[i]);
	}
	return (0);
}
