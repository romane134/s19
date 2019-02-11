/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 14:40:48 by rlucas-d          #+#    #+#             */
/*   Updated: 2019/02/10 16:59:25 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

t_test			*ft_sort_list(int flag, t_test *list)
{
	struct stat		s;
	t_test			*debut;

	flag++;
	debut = list;
	while (list)
	{
		if (!(list->list.path = ft_strjoin("./", list->list.name)))
			return (NULL);
		lstat(list->list.path, &s);
		stat_time(s, &list->list);
		list = list->next;
	}
	list = debut;
	return (list);
}

void			ft_sort(int flag, t_test *file)
{
	if ((flag & T_FLAG) == T_FLAG)
		sort_list_time(file);
	if ((flag & R_FLAG) == R_FLAG)
		file = list_rev(file);
	print_list(file);
	if ((flag & RR_FLAG) == RR_FLAG)
		ft_recur(flag, file);
}

void			sort_list_time(t_test *file)
{
	t_file		tp;
	t_test		*tmp;

	tmp = file;
	if (file == NULL)
		return ;
	while (file->next != NULL)
	{
		if (file->list.time < file->next->list.time)
		{
			tp = file->list;
			file->list = file->next->list;
			file->next->list = tp;
			file = tmp;
		}
		else
			file = file->next;
	}
	file = tmp;
}

t_test			*list_rev(t_test *file)
{
	t_test			*tmp;
	t_test			*element;

	tmp = NULL;
	if (file == NULL)
		return (file);
	while (file != NULL)
	{
		if (!(element = malloc(sizeof(*element))))
			return (NULL);
		element->list = file->list;
		if (tmp == NULL)
			element->next = NULL;
		else
			element->next = tmp;
		tmp = element;
		file = file->next;
	}
	return (tmp);
}

void			sort_list(t_test *file)
{
	t_file		tp;
	t_test		*tmp;

	tmp = file;
	if (file == NULL)
		return ;
	while (file->next != NULL)
	{
		if (ft_strcmp(file->list.name, file->next->list.name) > 0)
		{
			tp = file->list;
			file->list = file->next->list;
			file->next->list = tp;
			file = tmp;
		}
		else
			file = file->next;
	}
	file = tmp;
}
