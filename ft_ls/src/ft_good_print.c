/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_good_print.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 14:21:09 by rlucas-d          #+#    #+#             */
/*   Updated: 2019/01/30 13:05:53 by smondesi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int		ft_tot_blks(t_test *li)
{
	int i;

	i = 0;
	while (li != NULL)
	{
		i = i + li->doki.blks;
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

void	ft_space(int i)
{
	while (i--)
		st_printf(" ");
}

void	ft_totspace(t_test *li, t_space *i)
{
	i->link = 0;
	i->size = 0;
	i->group = 0;
	i->user = 0;
	i->minor = 0;
	i->major = 0;
	while (li != NULL)
	{
		if (i->link < ft_lg(li->doki.link))
			i->link = ft_lg(li->doki.link);
		if (i->size < ft_lg(li->doki.size))
			i->size = ft_lg(li->doki.size);
		if (i->group < ft_strlen(li->doki.group))
			i->group = ft_strlen(li->doki.group);
		if (i->user < ft_strlen(li->doki.user))
			i->user = ft_strlen(li->doki.user);
		if (i->major < ft_lg(li->doki.major))
			i->major = ft_lg(li->doki.major) + 1;
		if (i->minor < ft_lg(li->doki.minor))
			i->minor = ft_lg(li->doki.minor) + 2;
		li = li->next;
	}
}
