/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 14:40:48 by rlucas-d          #+#    #+#             */
/*   Updated: 2019/01/31 17:16:19 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void			ft_sort(int flag, t_test *file)
{
	//sort_list(file);
	if ((flag & T_FLAG) == T_FLAG)
		sort_list_time(file);
	if ((flag & R_FLAG) == R_FLAG)
		file = list_rev(file);
	print_list(file);
	if ((flag & RR_FLAG) == RR_FLAG)
		ft_recur(flag, file);
}

void		sort_list_time(t_test *file)
{
	t_file		tp;
	t_test		*tmp;

	tmp = file;
	if (file == NULL)
		return ;
	while (file->next != NULL)
	{
		if (file->doki.time < file->next->doki.time)
		{
			tp = file->doki;
			file->doki = file->next->doki;
			file->next->doki = tp;
			file = tmp;
		}
		else
			file = file->next;
	}
	file = tmp;
}

t_test		*list_rev(t_test *file)
{
	t_test			*tmp;
	t_test			*element;

	tmp = NULL;
	if (file == NULL)
		return (file);
	while (file != NULL)
	{
		element = malloc(sizeof(*element));
		element->doki = file->doki;
		if (tmp == NULL)
			element->next = NULL;
		else
			element->next = tmp;
		tmp = element;
		file = file->next;
	}
	return (tmp);
}

void		sort_list(t_test *file)
{
	t_file		tp;
	t_test		*tmp;

	tmp = file;
	if (file == NULL)
		return ;
	while (file->next != NULL)
	{
		if (ft_strcmp(file->doki.name, file->next->doki.name) > 0)
		{
			tp = file->doki;
			file->doki = file->next->doki;
			file->next->doki = tp;
			file = tmp;
			//	print_list(file);
		}
		else
			file = file->next;
	}
	file = tmp;
}
