/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lecture.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 13:52:52 by rlucas-d          #+#    #+#             */
/*   Updated: 2019/01/21 19:31:48 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

/*void		lecture(int flag, char *doc)
{
	DIR				*dirp;
	struct dirent	*dp;
	char			*fludg;
	t_file			*file;

	file = NULL;
	if (!(dirp = opendir(doc)))
	{
		st_printf("ls: %s\n", strerror(errno));
		exit(0);
	}
	doc = ft_strjoin(doc, "/");
	while ((dp = readdir(dirp)) != NULL)
	{
		fludg = ft_strjoin(doc, dp->d_name);
		file->name = dp->d_name;
		//(((flag & A_FLAG) != 0)
		if (((flag & L_FLAG) == L_FLAG))
			print_info_file(fludg, *file);
		//	lecture(flag, fludg);
		//st_printf("\n");
		st_printf("%s\n", file->name);
	}
	closedir(dirp);
}*/

t_test		*lecture(int flag, char *doc)
{
	DIR				*dirp;
	struct dirent	*dp;
	t_file			data;
	t_test			*file;
	struct s_test		*element;

	if (!(dirp = opendir(doc)))
	{
		st_printf("ls: %s\n", strerror(errno));
		exit(0);
	}
	doc = ft_strjoin(doc, "/");
	file = NULL;
	while ((dp = readdir(dirp)) != NULL)
	{
		if (dp->d_name[0] != '.' || (flag & A_FLAG) == A_FLAG)
		{
			element = malloc(sizeof(*element));
			data.flag = flag;
			data.path = ft_strjoin(doc, dp->d_name);
			data.name = dp->d_name;
			ft_inspect_file(data.path, &data);
			element->doki = data;
			if (file == NULL)
			{
				element->next = NULL;
			}
			else
			{
				element->next = file;
			}
			file = element;
		}
	}
	closedir(dirp);
	return (file);
}
