/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smondesi <smondesi@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 11:42:10 by smondesi          #+#    #+#             */
/*   Updated: 2019/06/27 14:57:33 by sstinglh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static int			ft_find_command(t_filename **fname, char *cmd)
{
	int		i;
	int		nb;
	t_hash	*hash;

	i = 0;
	nb = 0;
	while (i < HASHTABLE_SIZE)
	{
		hash = g_hash_table[i];
		while (hash != NULL)
		{
			if (ft_strcmpstart(cmd, hash->key))
			{
				nb++;
				*fname = ft_add_list(*fname, hash->key);
			}
			hash = hash->next;
		}
		i++;
	}
	return (nb);
}

char				*autocomplete_command(char *cmd, int *i)
{
	int				nb;
	char			*tmp;
	t_filename		*fname;
	t_filename		*start;

	fname = NULL;
	nb = ft_find_command(&fname, cmd);
	start = fname;
	if (nb == 1)
	{
		tmp = ft_strdup(fname->file);
		ft_del_list(fname);
		*i = 1;
		return (tmp);
	}
	else if (nb > 1 && ft_printf("\n"))
		while (fname)
		{
			*i = 1;
			ft_printf("%s\n", fname->file);
			fname = fname->next;
		}
	ft_del_list(start);
	return (ft_strdup(cmd));
}
