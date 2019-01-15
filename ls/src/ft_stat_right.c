/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stat_right.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 17:06:25 by rlucas-d          #+#    #+#             */
/*   Updated: 2019/01/15 12:02:13 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"
#include <grp.h>

#include <unistd.h>

t_file		ft_inspect_file(struct stat s, t_file file)
{
	struct group	*group;
	struct passwd	*pwd;

	pwd = getpwuid(s.st_uid);
	group = getgrgid(s.st_gid);
	file.mode = ft_strnew(11);
	file.mode[0] = ((s.st_mode & S_IFDIR) ? 'd' : '-');
	file.mode[1] = ((s.st_mode & S_IRUSR) ? 'r' : '-');
	file.mode[2] = ((s.st_mode & S_IWUSR) ? 'w' : '-');
	file.mode[3] = ((s.st_mode & S_IXUSR) ? 'x' : '-');
	file.mode[4] = ((s.st_mode & S_IRGRP) ? 'r' : '-');
	file.mode[5] = ((s.st_mode & S_IWGRP) ? 'w' : '-');
	file.mode[6] = ((s.st_mode & S_IXGRP) ? 'x' : '-');
	file.mode[7] = ((s.st_mode & S_IROTH) ? 'r' : '-');
	file.mode[8] = ((s.st_mode & S_IWOTH) ? 'w' : '-');
	file.mode[9] = ((s.st_mode & S_IXOTH) ? 'x' : '-');
	file.link = (int)s.st_nlink;
	file.user = pwd->pw_name;
	file.group = group->gr_name;
	file.size = (int)s.st_size;
	file.date = ft_strsub(ctime((const long *)&s.st_mtimespec), 4, 12);
	return (file);
}

int  analyse_file(char *doc, t_file file)
{
	struct stat s;


	if((stat(doc, &s) == -1) && (lstat(doc, &s) == -1) && (S_ISLNK(s.st_mode)))
	{
		strerror(errno);
		exit(EXIT_FAILURE);
	}
	file = ft_inspect_file(s, file);
	st_printf("%s ", file.mode);
	//	st_printf("The file %s a symbolic link\n\n", (S_ISLNK(s.st_mode)) ? "is" : "is not");
	return (0);
}
