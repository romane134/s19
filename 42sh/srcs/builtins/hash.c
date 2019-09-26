/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smondesi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 20:45:35 by smondesi          #+#    #+#             */
/*   Updated: 2019/08/29 18:07:01 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	hash_builtin(void)
{
	int		i;
	t_hash	*hash;

	i = 0;
	while (i < HASHTABLE_SIZE)
	{
		hash = g_hash_table[i];
		while (hash != NULL)
		{
			if (hash->nb > 0)
				ft_printf("%d %s\n", hash->nb, hash->data);
			hash = hash->next;
		}
		i++;
	}
}
