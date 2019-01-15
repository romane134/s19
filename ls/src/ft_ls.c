/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 13:38:41 by rlucas-d          #+#    #+#             */
/*   Updated: 2019/01/15 16:25:27 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 ** @ means the file has extended attributes. Use listxattr() to get a list 
 ** of the names of all the extended attributes, and getxattr() to get the 
 ** value of a particular attribute. If listxattr returns a non-zero result,
 ** you would display @ to indicate this.
 */


#include "../includes/ft_ls.h"

void	lecture(int flag, char *doc)
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
		/*if (((flag & A_FLAG) != 0) && ((ft_strcmp(file.name, ".") != 0) || (ft_strcmp(file.name, "..") != 0/))
		{
			continue;
		}*/
		if (((flag & L_FLAG) == L_FLAG))
			analyse_file(fludg, file);
				//	lecture(flag, fludg);
		//st_printf("\n");
		st_printf("%s\n", file.name);
	}
	closedir(dirp);
}

void		ft_what_kind(char *flags, char *doc)
{
	(void)flags;
	struct stat s;
	t_file			file;

	if ((stat(doc, &s) == -1))
	{
		st_printf("stat: %s\n", strerror(errno));
	}
	if (!(opendir(doc)))
	{
		file.name = doc;
	}
}


int main (int argc, char **argv)
{
	//struct stat s;
	int flag;
	int i;
	(void)argc;
	flag = 0;
	i = ft_flag(argv, &flag);
	if (i > argc)
		lecture(flag, ".");
	else
		lecture(flag, argv[i]);
	return (0);
}





/* savoir si @, +, - !!!!!
 *
 * acl_t acl = NULL;
 acl_entry_t dummy;
 ssize_t xattr = 0;
 char str[10];
 char * filename = "/Applications";

 acl = acl_get_link_np(filename, ACL_TYPE_EXTENDED);
 if (acl && acl_get_entry(acl, ACL_FIRST_ENTRY, &dummy) == -1) {
 acl_free(acl);
 acl = NULL;
 }
 xattr = listxattr(filename, NULL, 0, XATTR_NOFOLLOW);
 if (xattr < 0)
 xattr = 0;

 str[1] = '\0';
 if (xattr > 0)
 str[0] = '@';
 else if (acl != NULL)
 str[0] = '+';
 else
 str[0] = ' ';

 printf("%s\n", str);
 */

