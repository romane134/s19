/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 14:17:58 by rlucas-d          #+#    #+#             */
/*   Updated: 2019/02/10 17:15:48 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

t_test			*add_lst(t_test *li, t_file data)
{
	struct s_test *element;

	if (!(element = malloc(sizeof(*element))))
		return (NULL);
	element->list = data;
	if (li == NULL)
		element->next = NULL;
	else
		element->next = li;
	return (element);
}

t_test			*push_back_list(t_test *li, t_file data)
{
	t_test *element;
	t_test *temp;

	if (!(element = malloc(sizeof(*element))))
		return (NULL);
	element->list = data;
	element->next = NULL;
	if (li == NULL)
		return (element);
	temp = li;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = element;
	return (li);
}

t_test			*add_sort(t_test *li, t_file data)
{
	t_test *tmp;
	t_test *element;

	tmp = li;
	if (li == NULL || ft_strcmp(li->list.name, data.name) > 0)
		return (li = add_lst(li, data));
	while (li->next != NULL && ft_strcmp(li->next->list.name, data.name) < 0)
		li = li->next;
	if (li->next == NULL)
	{
		li = tmp;
		li = push_back_list(li, data);
	}
	else
	{
		if (!(element = malloc(sizeof(*element))))
			return (NULL);
		element->list = data;
		element->next = li->next;
		li->next = element;
	}
	li = tmp;
	return (li);
}

void			ft_free_list(t_test *child)
{
	t_test *next;

	while (child != NULL)
	{
		next = child->next;
		ft_memdel((void**)&child->list.path);
		ft_memdel((void**)&child->list.name);
		ft_memdel((void**)&child->list.date);
		ft_memdel((void**)&child->list.mode);
		ft_memdel((void**)&child->list.user);
		ft_memdel((void**)&child->list.group);
		ft_memdel((void**)&child);
		child = next;
	}
}
