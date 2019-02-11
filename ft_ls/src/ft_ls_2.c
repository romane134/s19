/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 17:48:31 by rlucas-d          #+#    #+#             */
/*   Updated: 2019/02/11 14:23:40 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

t_test			*ft_file(t_test *list, int link)
{
	struct stat	s;
	DIR			*dir;
	t_test		*file;

	file = NULL;
	while (list)
	{
		if (((lstat(list->list.name, &s) != -1) && (!(dir =
							opendir((list->list.name))))) || (link == 1))
			push_back(&file, ft_list(list->list.name));
		else
			closedir(dir);
		list = list->next;
	}
	return (file);
}

void			ft_list_document(t_test *list, int flag, int i, int link)
{
	DIR			*dir;
	int			count;
	int			start;

	start = 0;
	count = 1;
	while (list)
	{
		if ((dir = opendir((list->list.name))) && (link != 1))
		{
			list->list.tot = 0;
			if (start != 0)
				st_printf("\n");
			if (i >= 2)
				st_printf("%s:\n", list->list.name);
			ft_sort(flag, lecture(flag, list->list.name));
			if (start == 0)
				start = 1;
		}
		list = list->next;
		closedir(dir);
	}
	ft_free_list(list);
}
