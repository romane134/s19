/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   highlight.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstinglh <sstinglh@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 13:55:15 by sstinglh          #+#    #+#             */
/*   Updated: 2019/06/27 14:57:50 by sstinglh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		highlight(t_termcaps *termcaps)
{
	ft_putstr(tparm(termcaps->highlight_color, COLOR_WHITE));
	ft_putstr(tparm(termcaps->text_color, COLOR_BLACK));
}

void		reset_highlight(t_termcaps *termcaps)
{
	ft_putstr(termcaps->reset);
}

/*
** print_highlight()
** On free la selection precedente car on va la remalloc
** On malloc select avec la taille de la nouvelle selection
** On affiche jusqu'au lus petit entre pos et start (depart curseur)
** Ensuite on highlight
** On print et save dans tmp_select jusqu'au plus grand entre pos et start
**				(fin curseur)
** On reset_highlight()
** On affiche la suite de la commande
*/

void		print_highlight(t_termcaps *termcaps, char *cmd)
{
	int i;
	int y;

	i = 0;
	y = 0;
	del_line(termcaps);
	display_name();
	ft_bzero(termcaps->tmp_select, NAME_MAX);
	while (i < termcaps->cc_start && i < termcaps->pos)
		ft_putchar(cmd[i++]);
	highlight(termcaps);
	if (termcaps->cc_start == termcaps->pos)
	{
		reset_highlight(termcaps);
		ft_putstr(cmd + i);
		return ;
	}
	while (i < bigger(termcaps->cc_start, termcaps->pos))
	{
		termcaps->tmp_select[y++] = cmd[i];
		ft_putchar(cmd[i]);
		i++;
	}
	reset_highlight(termcaps);
	ft_putstr(cmd + i);
}

/*
** cut_in_cmd()
** couper la commande selectionnee avec le edit-edit_mode
** on coupe la partie qui se trouve |e| t->pos et t->cc_start
** on copie la string de la pos 0 jusqu'a le debut de la partie selectionnee
** puis de la fin de la partie selectionnee a la fin de la string
*/

void		cut_in_cmd(t_termcaps *t, char **cmd)
{
	char	*tmp;
	char	*new;
	int		i;
	int		y;

	i = 0;
	y = 0;
	tmp = *cmd;
	new = ft_strnew(ft_strlen(*cmd) - val_abs(t->cc_start -
		t->pos));
	while ((tmp[y]) && (i < smaller(t->cc_start, t->pos)) && i <
		(int)ft_strlen(*cmd))
		new[i++] = tmp[y++];
	y = bigger(t->cc_start, t->pos);
	while (tmp[y])
		new[i++] = tmp[y++];
	ft_strdel(cmd);
	*cmd = ft_strdup(new);
	ft_strdel(&new);
}
