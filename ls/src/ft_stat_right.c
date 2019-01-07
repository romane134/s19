/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stat_right.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 17:06:25 by rlucas-d          #+#    #+#             */
/*   Updated: 2019/01/07 17:11:06 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int		ft_inspect_rep(char *file, struct stat s)
{
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
	st_printf(" rlucas-d  2018 ");
	st_printf("%d",(int)s.st_size);
//total --> st_blocks

	//nt_printf(" Dec 13 15:51 ");
	st_printf("%s\n", file);
	return (0);
}

int		ft_inspect_file(char *file, struct stat s)
{

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
	st_printf(" rlucas-d  2018 ");
	st_printf("%d ",(int)s.st_size);

	//nt_printf(" Dec 13 15:51 ");
	st_printf("%s\n", file);
	return (0);
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
		ft_inspect_rep(file, s);
	else
		ft_inspect_file(file, s);
	st_printf("The file %s a symbolic link\n\n", (S_ISLNK(s.st_mode)) ? "is" : "is not");

	return (0);
}

