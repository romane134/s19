/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stat_right.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 17:06:25 by rlucas-d          #+#    #+#             */
/*   Updated: 2019/02/10 17:23:25 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static char		*permissions(struct stat s, t_file *file)
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
	str[9] = ft_atrib(file);
	return (str);
}

static char		*ft_filetype(struct stat s)
{
	char *str;

	str = ft_strnew(1);
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
	return (str);
}

static char		*stat_2(ssize_t var_time)
{
	char	*tmp;
	char	*date;
	char	*tmppp;

	if (!(tmp = ft_strsub(ctime((const long *)&var_time), 19, 5)))
		return (NULL);
	if (!(date = ft_strsub(ctime((const long *)&var_time), 4, 7)))
		return (NULL);
	tmppp = date;
	if (!(date = ft_strjoin(tmppp, tmp)))
		return (NULL);
	free(tmppp);
	return (date);
}

char			*stat_time(struct stat s, t_file *file)
{
	char	*date;
	ssize_t	var_time;
	int		age;

	if (file->flag & U_FLAG)
		var_time = s.st_atime;
	else if (file->flag & UU_FLAG)
		var_time = s.st_birthtime;
	else
		var_time = s.st_mtime;
	age = time(0) - var_time;
	if ((file->flag & TT_FLAG) == TT_FLAG)
		date = ft_strsub((ctime((const long *)&var_time)), 4, 20);
	else if (age > -15778800 && age < 15778800)
		date = ft_strsub((ctime((const long *)&var_time)), 4, 12);
	else if (var_time == 253402297200)
		date = "Jan  1  10000";
	else
		date = stat_2(var_time);
	file->time = var_time;
	return (date);
}

t_file			ft_inspect_file(t_file *file)
{
	char			*str;
	char			*tmp;
	struct stat		s;

	lstat(file->path, &s);
	file->gr = getgrgid(s.st_gid);
	tmp = ft_filetype(s);
	str = permissions(s, file);
	file->mode = ft_strjoin(tmp, str);
	ft_memdel((void**)&str);
	ft_memdel((void**)&tmp);
	file->link = (int)s.st_nlink;
	file->major = major(s.st_rdev);
	file->minor = minor(s.st_rdev);
	if (!(file->pwd = getpwuid(s.st_uid)))
		file->user = ft_itoa(s.st_uid);
	else
		file->user = ((file->flag & N_FLAG) ? ft_itoa(s.st_uid)
				: ft_strdup(file->pwd->pw_name));
	file->group = ((file->flag & N_FLAG) ? ft_itoa(s.st_gid) :
			ft_strdup(file->gr->gr_name));
	file->size = (int)s.st_size;
	file->date = stat_time(s, file);
	file->blks = s.st_blocks;
	return (*file);
}
