/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smondesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 11:26:54 by smondesi          #+#    #+#             */
/*   Updated: 2019/01/07 17:05:29 by smondesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include "libft/libft.h"
#include <time.h>
#include <pwd.h>

void	flag_l(char *str, struct stat *buf)
{
	struct passwd *pwd;

	pwd = getpwuid(buf->st_uid);
	st_printf (" %s ", pwd->pw_name);//nom uid
	st_printf(" %d ", buf->st_size); //taille
	st_printf(" %s ", ctime(&buf->st_mtimespec));
	st_printf(" %d ", buf->st_nlink);//collone 2 (nbr de lien)
}

void	test(char *fd, char *flag)
{
	DIR *dirp;
	struct dirent  *dp;
	struct stat *buf;
	char	*fludg;


	fd = ft_strjoin(fd, "/");
	dirp = opendir(fd);
	while ((dp = readdir(dirp)) != NULL)
	{
		if(dp->d_name[0] != '.' || ft_strchr(flag, 'a') != NULL)
		{
			buf = (struct stat *)malloc(sizeof(struct stat));
			fludg = ft_strjoin(fd, dp->d_name);
			stat(fludg, buf);
		//	printf("**%hu", buf->st_mode);
			if (ft_strchr(flag, 'l') != NULL)
				flag_l(fludg, buf);
			st_printf("%s\n", dp->d_name);
			if (buf->st_mode == 16877 && ft_strchr(flag, 'R') != NULL && ft_strcmp(dp->d_name, ".") != 0 && ft_strcmp(dp->d_name, "..") != 0)
			{
				free(buf);
				st_printf("\n%s\n", fludg);
				test(fludg, flag);
			}
			else
				free (buf);
		}
	}
	closedir(dirp);
}

void	which_flag(char **argv, int argc)
{
	char *flag;
	char *doc;
	int	i;

	i = 1;
	flag = ft_strnew(0);
	doc = ft_strnew(0);
	while (i < argc)
	{
		if (argv[i][0] == '-')
			flag = ft_strjoin(flag, argv[i]);
		else
		{
			doc = ft_strnew(ft_strlen(argv[i]));
			doc = argv[i];
	 	break ;
		}
		i++;
	}
	if (doc[0] == '\0')
		ft_memset(doc, '.', 1);
	st_printf("-->%s\n", doc);
	test(doc, flag);
}

int main(int argc, char **argv)
{
	which_flag(argv, argc);	
//	test(argv[argc - 1], "po");
//	test(argv[argc - 1], argv[1]);
}
