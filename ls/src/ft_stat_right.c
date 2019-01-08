/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stat_right.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 17:06:25 by rlucas-d          #+#    #+#             */
/*   Updated: 2019/01/08 12:32:10 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"
#include <time.h>

void		ft_inspect_rep(struct stat s)
{
	struct passwd *pwd;
	char *date;

	pwd = getpwuid(s.st_uid);
		//nt_printf("File inode: \t\t%d\n",(int)s.st_ino);
	st_printf("d");
	st_printf((s.st_mode & S_IRUSR) ? "r" : "-");
	st_printf((s.st_mode & S_IWUSR) ? "w" : "-");
	st_printf((s.st_mode & S_IXUSR) ? "x" : "-");
	st_printf((s.st_mode & S_IRGRP) ? "r" : "-");
	st_printf((s.st_mode & S_IWGRP) ? "w" : "-");
	st_printf((s.st_mode & S_IXGRP) ? "x" : "-");
	st_printf((s.st_mode & S_IROTH) ? "r" : "-");
	st_printf((s.st_mode & S_IWOTH) ? "w" : "-");
	st_printf((s.st_mode & S_IXOTH) ? "x" : "-");
	st_printf(" ");
	st_printf("%d",(int)s.st_nlink);
	st_printf(" %s", pwd->pw_name);
	st_printf(" 2018 ");
	st_printf("%d",(int)s.st_size);
	date = ft_strsub(ctime((const long *)&s.st_mtimespec), 4, 12);
	st_printf(" %s ", date);
	//st_printf("%s\n", file);
}

void		ft_inspect_file(struct stat s)
{
	struct passwd *pwd;
	char *date;

	pwd = getpwuid(s.st_uid);
	st_printf("-");
	st_printf((s.st_mode & S_IRUSR) ? "r" : "-");
	st_printf((s.st_mode & S_IWUSR) ? "w" : "-");
	st_printf((s.st_mode & S_IXUSR) ? "x" : "-");
	st_printf((s.st_mode & S_IRGRP) ? "r" : "-");
	st_printf((s.st_mode & S_IWGRP) ? "w" : "-");
	st_printf((s.st_mode & S_IXGRP) ? "x" : "-");
	st_printf((s.st_mode & S_IROTH) ? "r" : "-");
	st_printf((s.st_mode & S_IWOTH) ? "w" : "-");
	st_printf((s.st_mode & S_IXOTH) ? "x" : "-");
	st_printf("  ");
	st_printf("%d",(int)s.st_nlink);
	st_printf(" %s", pwd->pw_name);
	st_printf(" 2018 ");
	st_printf("%d ",(int)s.st_size);
	date = ft_strsub(ctime((const long *)&s.st_mtimespec), 4, 12);
	st_printf(" %s ", date);
	//	st_printf("%s\n", file);
}

int  analyse_file(char *file)
{
	struct stat s;

	if((stat(file, &s) == -1) && (lstat(file, &s) == -1) && (S_ISLNK(s.st_mode)))
	{
		perror("coucou");
		exit(EXIT_FAILURE);
	}

	if (s.st_mode&S_IFDIR)
		ft_inspect_rep(s);
	else
		ft_inspect_file(s);
//	st_printf("The file %s a symbolic link\n\n", (S_ISLNK(s.st_mode)) ? "is" : "is not");

	return (0);
}
