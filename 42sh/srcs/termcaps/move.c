/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstinglh <sstinglh@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 13:59:40 by sstinglh          #+#    #+#             */
/*   Updated: 2019/06/27 15:36:31 by sstinglh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
** go_left()
** Deplace le curseur vers la gauche
** On fait pos - 1
** Si on est en edit_mode, il faut highlight et ajouter a tmp_select
** Pour cela on save le curseur, on efface la ligne, on display le prompt,
** On utilise print_highlight pour afficher la selection et gerer tmp_select
** On restore la position du curseur et on decale sur la gauche
*/

void	go_left(t_termcaps *termcaps, char **cmd)
{
	termcaps->pos--;
	if (termcaps->edit_mode)
		show_new(*cmd, termcaps, 1);
	else
		tputs(tgoto(termcaps->goleft, 0, 0), 1, (void *)ft_putchar);
}

/*
** go_right()
** Deplace le curseur vers la droite
** On fait pos + 1
** Si on est en edit_mode, il faut highlight et ajouter a tmp_select
** Pour cela on save le curseur, on efface la ligne, on display le prompt,
** On utilise print_highlight pour afficher la selection et gerer tmp_select
** On restore la position du curseur et on decale sur la droite
*/

void	go_right(t_termcaps *termcaps, char **cmd)
{
	termcaps->pos++;
	if (termcaps->edit_mode)
		show_new(*cmd, termcaps, 1);
	else
		tputs(tgoto(termcaps->goright, 0, 0), 1, (void *)ft_putchar);
}

void	down_one_line(t_termcaps *t)
{
	int i;

	i = 0;
	tputs(tgoto(t->godown, 0, 0), 1, (void *)ft_putchar);
	while (i < (t->pos + t->path) % t->size)
	{
		i++;
		tputs(tgoto(t->goright, 0, 0), 1, (void *)ft_putchar);
	}
	t->pos = t->pos + t->size;
}
