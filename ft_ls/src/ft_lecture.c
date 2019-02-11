/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lecture.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 14:32:06 by rlucas-d          #+#    #+#             */
/*   Updated: 2019/02/10 16:58:34 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

t_test			*lecture_2(int flag, struct dirent *dp, char *doc, t_test *file)
{
	t_file		data;

	if ((flag & A_FLAG) == A_FLAG || dp->d_name[0] != '.')
	{
		data.flag = flag;
		if (!(data.path = ft_strjoin(doc, dp->d_name)))
			return (NULL);
		if (!(data.name = ft_strdup(dp->d_name)))
			return (NULL);
		ft_inspect_file(&data);
		file = ((flag & F_FLAG) ? push_back_list(file, data) :
				add_sort(file, data));
	}
	return (file);
}

t_test			*lecture(int flag, char *doc)
{
	DIR					*dirp;
	struct dirent		*dp;
	t_test				*file;

	file = NULL;
	if (!(dirp = opendir(doc)))
	{
		st_printf_error("ls: %s: %s\n", (ft_strrchr((const char *)doc, '/') + 1)
				, strerror(errno));
		return (NULL);
	}
	if (!(doc = ft_strjoin(doc, "/")))
		return (NULL);
	file = NULL;
	while ((dp = readdir(dirp)) != NULL)
		file = lecture_2(flag, dp, doc, file);
	ft_memdel((void**)&doc);
	closedir(dirp);
	return (file);
}

int				ft_link(int flag, t_test *list)
{
	struct stat		s;

	if (!(flag & L_FLAG))
		return (0);
	if (list->list.name[0] == '-')
		return (0);
	if ((lstat(list->list.name, &s) != -1))
	{
		if (S_ISLNK(s.st_mode))
		{
			if ((stat(list->list.name, &s) != -1))
			{
				if ((s.st_mode & S_IFMT) == S_IFDIR)
					return (1);
			}
		}
	}
	return (0);
}
