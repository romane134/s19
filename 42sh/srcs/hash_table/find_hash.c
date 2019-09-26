/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_hash.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 16:08:06 by vjovanov          #+#    #+#             */
/*   Updated: 2019/08/29 18:18:48 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	*find_hash(t_hash **array, char *key, int i)
{
	int			index;
	t_hash		*start;
	char		*data;

	index = find_index_key(key, i);
	start = array[index];
	while (array[index] != NULL && ft_strcmp(array[index]->key, key))
		array[index] = array[index]->next;
	if (array[index] == NULL)
	{
		array[index] = start;
		return (NULL);
	}
	array[index]->nb++;
	data = array[index]->data;
	array[index] = start;
	return (data);
}
