/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_hash.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 16:07:56 by vjovanov          #+#    #+#             */
/*   Updated: 2019/07/16 10:13:38 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static void		add_end(char *key, t_hash **array, t_hash *add, int i)
{
	t_hash *tp;

	tp = array[i];
	if (ft_strcmp(tp->key, key) == 0)
	{
		add->next = tp->next;
		ft_strdel(&tp->key);
		free(tp->data);
		free(tp);
		array[i] = add;
		return ;
	}
	while (tp->next != NULL && (ft_strcmp(tp->next->key, key)))
		tp = tp->next;
	if (tp->next != NULL && !(ft_strcmp(tp->next->key, key)))
// si on n'est pas a la fin et qu'il a la meme key
	{
		if (tp->next)
			add->next = tp->next->next;
		ft_strdel(&tp->next->key);
		ft_memdel(&tp->next->data);
		free(tp->next);
		tp->next = add;
	}
	else
		tp->next = add;
}

void			add_data_hash(char *key, void *data, int size, t_hash **array)
{
	t_hash	*tmp;
	int		i;

	i = find_index_key(key, size);
	tmp = malloc(sizeof(*tmp));
	tmp->key = key;
	tmp->data = data;
	tmp->nb = 0;
	tmp->next = NULL;
	if (array[i] == NULL)
	{
		array[i] = tmp;
		return ;
	}
	add_end(key, array, tmp, i);
}
