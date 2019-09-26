/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_fonction.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 16:08:12 by vjovanov          #+#    #+#             */
/*   Updated: 2019/05/22 16:08:13 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		total_ascii(char *s)
{
	int i;
	int rep;

	rep = 0;
	i = 0;
	while (s[i])
	{
		rep += s[i];
		i++;
	}
	return (rep);
}

int		find_index_key(char *s, int size)
{
	int index;

	index = total_ascii(s) % size;
	return (index);
}

t_hash	**make_hash(int size)
{
	t_hash	**array;
	int		i;

	i = 0;
	array = malloc(sizeof(**array) * (size));
	while (i <= size)
	{
		array[i] = NULL;
		i++;
	}
	return (array);
}

void	print_all_hash_str(t_hash **array, int size)
{
	int		i;
	t_hash	*tmp;

	i = 0;
	while (i <= size)
	{
		tmp = array[i];
		while (tmp != NULL)
		{
			ft_printf("%s : %s = %d\n", tmp->key, tmp->data, tmp->nb);
			tmp = tmp->next;
		}
		i++;
	}
}
