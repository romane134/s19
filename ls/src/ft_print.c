/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 15:15:04 by rlucas-d          #+#    #+#             */
/*   Updated: 2019/01/31 17:15:56 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void		print_min_maj(t_test *li, t_space nb)
{
	if (li->doki.mode[0] == 'c' || li->doki.mode[0] == 'b')
	{
		ft_space(nb.major - ft_lg(li->doki.major));
		st_printf("%d,", li->doki.major);
		ft_space(nb.minor - ft_lg(li->doki.minor));
		st_printf("%d ", li->doki.minor);
	}
	else
	{
		if (nb.major > 0)
			ft_space(2);
		ft_space(nb.minor + nb.major);
		st_printf("%d ", li->doki.size);
	}
}

void		print_list_2(t_test *li, t_space nb)
{
	char	buf[1024];
	int		p;

	st_printf("%s  ", li->doki.mode);
	ft_space(nb.link - ft_lg(li->doki.link));
	st_printf("%d ", li->doki.link);
	st_printf("%s  ", li->doki.user);
	ft_space(nb.user - ft_strlen(li->doki.user));
	st_printf("%s  ", li->doki.group);
	ft_space(nb.group - ft_strlen(li->doki.group));
	ft_space(nb.size - ft_lg(li->doki.size));
	print_min_maj(li, nb);
	st_printf("%s ", li->doki.date);
	st_printf("%s ", li->doki.name);
	if (li->doki.mode[0] == 'l')
	{
		p = readlink(li->doki.path, buf, 1024);
		buf[p] = 0;
		st_printf("-> %s", buf);
	}
	st_printf("\n");
}

void		print_list(t_test *li)
{
	t_space i;

	if (li == NULL)
		return ;
	ft_totspace(li, &i);
	if ((li->doki.flag & L_FLAG) == L_FLAG)
		st_printf("total %d\n", ft_tot_blks(li));
	while (li != NULL)
	{
		if ((li->doki.flag & S_FLAG) == S_FLAG)
			st_printf("%d ", li->doki.blks);
		if ((li->doki.flag & L_FLAG) == L_FLAG)
			print_list_2(li, i);
		else
			st_printf("%s\n", li->doki.name);
		li = li->next;
	}
}
