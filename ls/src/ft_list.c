/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smondesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 11:54:35 by smondesi          #+#    #+#             */
/*   Updated: 2019/01/25 10:01:06 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void		sort_list_time(t_file *file)
{
	t_file		*tmp;

	tmp = file;
	if (file == NULL)
		return ;
	while (file->next != NULL)
	{
		if (file->time < file->next->time)
		{
			tmp = file;
			file = file->next;
			file->next = tmp;
		}
		else
			file = file->next;
	}
	file = tmp;
}

t_file		*list_rev(t_file *file)
{
	t_file			*tmp;

	tmp = NULL;
	if (file == NULL)
		return (file);
	while (file != NULL)
	{
		if (tmp == NULL)
			file->next = NULL;
		else
			file->next = tmp;
		tmp = file;
		file = file->next;
	}
	return (tmp);
}

void		sort_list(t_file *file, int (*cmp)(const char *a, const char *b))
{
	t_file		*tmp;

	tmp = file;
	if (file == NULL)
		return ;
	while (file->next != NULL)
	{
		if (cmp(file->name, file->next->name) > 0)
		{
			tmp = file;
			file = file->next;
			file->next = tmp;
		}
		else
			file = file->next;
	}
	file = tmp;
}
