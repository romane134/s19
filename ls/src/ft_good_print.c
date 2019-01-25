/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_good_print.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 14:21:09 by rlucas-d          #+#    #+#             */
/*   Updated: 2019/01/25 09:47:15 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int		ft_tot_blks(t_file *li)
{
	int i;

	i = 0;
	while (li != NULL)
	{
		i = i + li->blks;
		li = li->next;
	}
	return (i);
}

int		ft_lg(int nb)
{
	int i;

	i = 0;
	while (nb / 10 > 0)
	{
		i++;
		nb = nb / 10;
	}
	return (i);
}

int		ft_totspace(t_file *li)
{
	int i;

	i = 0;
	while (li != NULL)
	{
		if (i < li->link)
			i = li->link;
		li = li->next;
	}
	return (ft_lg(i));
}

int		ft_totspace_size(t_file *li)
{
	int i;

	i = 0;
	while (li != NULL)
	{
		if (i < li->size)
			i = li->size;
		li = li->next;
	}
	return (ft_lg(i));
}

void	ft_space(int i)
{
	while (i--)
		st_printf(" ");
}
