/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 15:15:04 by rlucas-d          #+#    #+#             */
/*   Updated: 2019/01/25 09:54:28 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void		print_list_2(t_file *li, int nb, int nbl)
{
	st_printf("%s  ", li->mode);
	ft_space(nb - ft_lg(li->link));
	st_printf("%d ", li->link);
	st_printf("%s  ", li->user);
	st_printf("%s  ", li->group);
	ft_space(nbl - ft_lg(li->size));
	st_printf("%d ", li->size);
	st_printf("%s ", li->date);
}

void			print_list(t_file *li)
{
	int		nb;
	int		nbl;

	if (li == NULL)
		return ;
	nb = ft_totspace(li);
	nbl = ft_totspace_size(li);
	if ((li->flag & L_FLAG) == L_FLAG)
		st_printf("total %d\n", ft_tot_blks(li));
	while (li != NULL)
	{
		if ((li->flag & S_FLAG) == S_FLAG)
			st_printf("%d ", li->blks);
		if ((li->flag & L_FLAG) == L_FLAG)
			print_list_2(li, nb, nbl);
		st_printf("%s\n", li->name);
		li = li->next;
	}
}
