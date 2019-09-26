/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_hash.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 16:08:01 by vjovanov          #+#    #+#             */
/*   Updated: 2019/06/29 19:00:27 by sstinglh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	del_hash(char *key, int size, t_hash **array)
{
	int		i;
	t_hash	*tmp;
	t_hash	*start;

	i = find_index_key(key, size);
	if (array[i] == NULL)
		return ;
	start = array[i];
	if (start != NULL && !(ft_strcmp(start->key, key)))
	{
		free(start);
		array[i] = array[i]->next;
		return ;
	}
	while (start->next != NULL && ft_strcmp(start->next->key, key))
		start = start->next;
	if (start->next == NULL)
		return ;
	tmp = start->next;
	start->next = start->next->next;
	free(tmp);
}

void	del_all_hash(t_hash **array, int size)
{
	int		i;
	t_hash	*tmp;

	i = 0;
	while (i <= size)
	{
		while (array[i] != NULL)
		{
			tmp = array[i];
			ft_memdel(&tmp->data);
			ft_strdel(&tmp->key);
			array[i] = array[i]->next;
			free(tmp);
		}
		free(array[i]);
		i++;
	}
	free(array);
}
