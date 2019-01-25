/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stat_right.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 17:06:25 by rlucas-d          #+#    #+#             */
/*   Updated: 2019/01/25 10:41:11 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"
#include <grp.h>

#include <unistd.h>

static char		*permissions(struct stat s)
{
	char *str;

	str = ft_strnew(10);
	str[0] = ((s.st_mode & S_IRUSR) ? 'r' : '-');
	str[1] = ((s.st_mode & S_IWUSR) ? 'w' : '-');
	if (s.st_mode & S_ISUID)
		str[2] = ((s.st_mode & S_IXUSR) ? 's' : 'S');
	else
		str[2] = ((s.st_mode & S_IXUSR) ? 'x' : '-');
	str[3] = ((s.st_mode & S_IRGRP) ? 'r' : '-');
	str[4] = ((s.st_mode & S_IWGRP) ? 'w' : '-');
	if (s.st_mode & S_ISGID)
		str[5] = ((s.st_mode & S_IXGRP) ? 's' : 'S');
	else
		str[5] = ((s.st_mode & S_IXGRP) ? 'x' : '-');
	str[6] = ((s.st_mode & S_IROTH) ? 'r' : '-');
	str[7] = ((s.st_mode & S_IWOTH) ? 'w' : '-');
	if (s.st_mode & S_ISVTX)
		str[8] = ((s.st_mode & S_IXUSR) ? 't' : 'T');
	else
		str[8] = ((s.st_mode & S_IXOTH) ? 'x' : '-');
	str[9] = '\0';
	return (str);
}

static char		*ft_filetype(struct stat s)
{
	char *str;

	str = ft_strnew(2);
	if ((s.st_mode & S_IFMT) == S_IFREG)
		str[0] = ('-');
	else if ((s.st_mode & S_IFMT) == S_IFSOCK)
		str[0] = ('s');
	else if ((s.st_mode & S_IFMT) == S_IFLNK)
		str[0] = ('l');
	else if ((s.st_mode & S_IFMT) == S_IFCHR)
		str[0] = ('c');
	else if ((s.st_mode & S_IFMT) == S_IFBLK)
		str[0] = ('b');
	else if ((s.st_mode & S_IFMT) == S_IFIFO)
		str[0] = ('f');
	else if ((s.st_mode & S_IFMT) == S_IFDIR)
		str[0] = ('d');
	str[1] = '\0';
	return (str);
}

char			*stat_time(struct stat s, t_file file)
{
	char	*date;
	int		var_time;
	int		age;

	if (file.flag & U_FLAG)
		var_time = s.st_atimespec.tv_sec;
	else if (file.flag & UU_FLAG)
		var_time = s.st_birthtimespec.tv_sec;
	else
		var_time = s.st_mtimespec.tv_sec;
	age = time(0) - var_time;
	if ((file.flag & TT_FLAG) == TT_FLAG)
		date = ft_strsub(ctime((const long *)&var_time), 4, 20);
	else if (age > 0 && age < 15778800)
		date = ft_strsub(ctime((const long *)&var_time), 4, 12);
	else
		date = ft_strsub(ctime((const long *)&var_time), 20, 4);
	return (date);
}

void			ft_inspect_file(char *doc, t_file *file)
{
	struct group	*group;
	struct passwd	*pwd;
	char			*str;
	struct stat		s;


	stat(doc, &s);
	pwd = getpwuid(s.st_uid);
	group = getgrgid(s.st_gid);
	file->mode = ft_strnew(10);
	file->mode = ft_filetype(s);
	str = permissions(s);
	file->mode = ft_strjoin(file->mode, str);
	free(str);
	file->link = (int)s.st_nlink;
	file->user = ((file->flag & N_FLAG) ? ft_itoa(s.st_uid) : pwd->pw_name);
	file->group = ((file->flag & N_FLAG) ? ft_itoa(s.st_gid) : group->gr_name);
	file->size = (int)s.st_size;
	file->date = stat_time(s, *file);
	file->blks = s.st_blocks;
	//file->name OK
}
