/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 14:40:48 by rlucas-d          #+#    #+#             */
/*   Updated: 2019/01/25 10:41:09 by rlucas-d         ###   ########.fr       */
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

	printf ("----%s\n", file->name);
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

void			ft_sort(int flag, t_file *file)
{
	sort_list(file, ft_strcmp);
	printf ("_____%s\n", file->name);
	if ((flag & T_FLAG) == T_FLAG)
		sort_list_time(file);
	if ((flag & R_FLAG) == R_FLAG)
		file = list_rev(file);
	print_list(file);
	if ((flag & RR_FLAG) == RR_FLAG)
		ft_recur(flag, file);
	printf ("iiiii%s\n", file->name);
}
