/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 15:15:04 by rlucas-d          #+#    #+#             */
/*   Updated: 2019/02/10 17:22:36 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void			print_min_maj(t_test *li, t_space nb)
{
	if (li->list.mode[0] == 'c' || li->list.mode[0] == 'b')
	{
		ft_space(nb.major - ft_lg(li->list.major));
		st_printf("%d,", li->list.major);
		ft_space(nb.minor - ft_lg(li->list.minor));
		st_printf("%d ", li->list.minor);
	}
	else
	{
		if (nb.major > 0)
			ft_space(2);
		ft_space(nb.minor + nb.major);
		st_printf("%d ", li->list.size);
	}
}

void			print_list_2(t_test *li, t_space nb)
{
	char	buf[1024];
	int		p;

	st_printf("%s ", li->list.mode);
	ft_space(nb.link - ft_lg(li->list.link));
	st_printf("%d ", li->list.link);
	st_printf("%s  ", li->list.user);
	ft_space(nb.user - ft_strlen(li->list.user));
	st_printf("%s  ", li->list.group);
	ft_space(nb.group - ft_strlen(li->list.group));
	ft_space(nb.size - ft_lg(li->list.size));
	print_min_maj(li, nb);
	st_printf("%s ", li->list.date);
	st_printf("%s", li->list.name);
	if (li->list.mode[0] == 'l')
	{
		p = readlink(li->list.path, buf, 1024);
		buf[p] = 0;
		st_printf(" -> %s", buf);
	}
	st_printf("\n");
}

void			print_list(t_test *li)
{
	t_space i;

	if (li == NULL)
		return ;
	ft_totspace(li, &i);
	if (((li->list.flag & L_FLAG) == L_FLAG) && (li->list.tot != 0))
		st_printf("total %d\n", ft_tot_blks(li));
	while (li != NULL)
	{
		if ((li->list.flag & S_FLAG) == S_FLAG)
			st_printf("%d ", li->list.blks);
		if (((li->list.flag & L_FLAG) == L_FLAG))
			print_list_2(li, i);
		else
			st_printf("%s\n", li->list.name);
		li = li->next;
	}
}
