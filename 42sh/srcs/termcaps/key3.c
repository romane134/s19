/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstinglh <sstinglh@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 15:38:58 by sstinglh          #+#    #+#             */
/*   Updated: 2019/06/27 15:39:08 by sstinglh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	left_key(t_termcaps *t, char **cmd)
{
	int i;

	i = -1;
	if ((t->pos + t->path) % t->size == 0)
	{
		t->pos--;
		tputs(tgoto(t->goup, 0, 0), 1, (void *)ft_putchar);
		while (i++ < t->size)
			tputs(tgoto(t->goright, 0, 0), 1, (void *)ft_putchar);
	}
	else
		go_left(t, cmd);
}

void	right_key(t_termcaps *t, char **cmd)
{
	if ((t->pos + t->path) % t->size >= t->size - 1)
	{
		t->pos++;
		tputs(tgoto(t->godown, 0, 0), 1, (void *)ft_putchar);
	}
	else
		go_right(t, cmd);
}
