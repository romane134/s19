/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 13:38:41 by rlucas-d          #+#    #+#             */
/*   Updated: 2019/01/25 10:41:08 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

t_file			*lecture(int flag, char *doc)
{
	DIR					*dirp;
	struct dirent		*dp;
	t_file				*file;

	file = NULL;
	if (!(dirp = opendir(doc)))
	{
		st_printf("ls: %s: %s\n", doc, strerror(errno));
		return (NULL);
	}
	doc = ft_strjoin(doc, "/");
	while ((dp = readdir(dirp)) != NULL)
	{
		if ((flag & A_FLAG) == A_FLAG || dp->d_name[0] != '.')
		{
			printf ("!\n");
			if (!(file = (t_file *)malloc(sizeof(*file))))
				return (NULL);
			file->flag = flag;
			file->path = ft_strjoin(doc, dp->d_name);
			file->name = dp->d_name;
			ft_inspect_file(file->path, file);
			printf ("%s\n", file->name); //file->name  OK;
			if (file == NULL)
				file->next = NULL;
			else
				file = file->next;
			printf ("iiii%s\n", file->name);
		}
	}
	closedir(dirp);
	return (file);
}

void			ft_recur(int flag, t_file *file)
{
	t_file	*child;

	while (file != NULL)
	{
		if (file->mode[0] == 'd' && ft_strcmp(file->name, ".") != 0 &&
				ft_strcmp(file->name, "..") != 0)
		{
			st_printf("\n%s:\n", file->path);
			child = lecture(flag, file->path);
			sort_list(child, ft_strcmp);
			print_list(child);
			ft_recur(flag, child);
			free(child);
		}
		file = file->next;
	}
}

int				main(int argc, char **argv)
{
	int		flag;
	int		i;
	t_file	*file;
	t_file	*list;
	struct stat s;

	list = (t_file*)malloc(sizeof(*list));
	flag = 0;
	i = ft_flag(argv, &flag);
	if (i == argc)
		file = lecture(flag, ".");

	while (i < argc)
	{
		if (opendir(argv[i]))
		{
			printf("\n%s:\n", argv[i]);
			file = lecture(flag, argv[i]);
			printf ("MAIN:   %s\n",file->name);
		}
		else if ((stat(argv[i], &s) != -1))
		{
			file = ft_lecture_file(flag, argv[i]);
//			ft_sort(flag, file);
			free(file);
			//i++;
		}
		else
			st_printf("ls: %s: %s\n", argv[i], strerror(errno));
		ft_sort(flag, file);
		i++;
	}
	return (0);
}
