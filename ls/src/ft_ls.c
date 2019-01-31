/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 13:38:41 by rlucas-d          #+#    #+#             */
/*   Updated: 2019/01/31 17:23:26 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

t_test	*add_lst(t_test *li, t_file data)
{
	struct s_test *element;

	element = malloc(sizeof(*element));
	element->doki = data;
	if (li == NULL)
		element->next = NULL;
	else
		element->next = li;
	return (element);
}

t_test	*push_back_list(t_test *li, t_file data)
{
	t_test *element;
	t_test *temp;

	element = malloc(sizeof(*element));
	if (element == NULL)
	{
		st_printf("Erreur : probleme allocation dynamique.\n");
		exit(EXIT_FAILURE);
	}
	element->doki = data;
	element->next = NULL;
	if (li == NULL)
		return (element);
	temp = li;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = element;
	return (li);
}

t_test	*add_sort(t_test *li, t_file data)
{
	t_test *tmp;
	t_test *element;

	tmp = li;
	if (li == NULL || ft_strcmp(li->doki.name, data.name) > 0)
		return (li = add_lst(li, data));
	while (li->next != NULL && ft_strcmp(li->next->doki.name, data.name) < 0)
		li = li->next;
	if (li->next == NULL)
	{
		li = tmp;
		li = push_back_list(li, data);
	}
	else
	{
		element = malloc(sizeof(*element));
		element->doki = data;
		element->next = li->next;
		li->next = element;
	}
	li = tmp;
	return (li);
}

t_test	*lecture(int flag, char *doc)
{
	DIR					*dirp;
	struct dirent		*dp;
	t_file				data;
	t_test				*file;

	if (!(dirp = opendir(doc)))
	{
		st_printf("ls: %s: %s\n", doc, strerror(errno));
		return (NULL);
	}
	doc = ft_strjoin(doc, "/");
	file = NULL;
	while ((dp = readdir(dirp)) != NULL)
	{
		if ((flag & A_FLAG) == A_FLAG || dp->d_name[0] != '.')
		{
			data.flag = flag;
			data.path = ft_strjoin(doc, dp->d_name);
			data.name = ft_strdup(dp->d_name);
			//data.name = dp->d_name;
			ft_inspect_file(&data);
			file = ((flag & F_FLAG) ? push_back_list(file, data) : add_sort(file, data));
		}
	}
	ft_memdel((void**)&doc);
	closedir(dirp);
	return (file);
}

void	ft_free_list(t_test *child)
{
	t_test *next;

	while (child != NULL)
	{
		next = child->next;
		ft_memdel((void**)&child->doki.path);
		ft_memdel((void**)&child->doki.name);
		ft_memdel((void**)&child->doki.date);
		ft_memdel((void**)&child->doki.mode);
		ft_memdel((void**)&child->doki.user);
		ft_memdel((void**)&child);
		child = next;
	}	
}

void	ft_recur(int flag, t_test *file)
{
	t_test	*child;

	child = NULL;
	while (file != NULL)
	{
		if (file->doki.mode[0] == 'd' && ft_strcmp(file->doki.name, ".") != 0 &&
				ft_strcmp(file->doki.name, "..") != 0)
		{
			st_printf("\n%s:\n", file->doki.path);
			child = lecture(flag, file->doki.path);
			ft_sort(flag, child);
			ft_free_list(child);
		}
		//	ft_free_list(file);
		file = file->next;
	}
}

int		main(int argc, char **argv)
{
	int			flag;
	int			i;
	int			j;
	t_test		*file;
	struct stat s;
	DIR			*dir;
	t_test		*list;


	flag = 0;
	i = ft_flag(argv, &flag);
	j = i;
	if (i == argc)
		file = lecture(flag, ".");
	if ((argc - i) >= 1)
	{
		list = ft_list_file(argv, i);
		while (list)
		{
			//printf("%s\n",list->doki.name);
			if ((dir = opendir((list->doki.name))))
			{
				printf("\n%s:\n", list->doki.name);
				file = lecture(flag, list->doki.name);
				ft_sort(flag, file);
			}
			else if ((stat(list->doki.name, &s) != -1))
			{
				list = ft_lecture_file(flag, list->doki.name);
				ft_print_file(list);
			}
			else
				st_printf("ls: %s: %s\n", list->doki.name, strerror(errno));
			if (dir != opendir((list->doki.name)))
				closedir(dir);
			list = list->next;
		}
	}
	return (0);
}
