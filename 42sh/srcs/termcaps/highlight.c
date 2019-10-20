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

void	highlight(t_termcaps *termcaps)
{
	ft_putstr(tparm(termcaps->highlight_color, COLOR_WHITE));
	ft_putstr(tparm(termcaps->text_color, COLOR_BLACK));
}

void	reset_highlight(t_termcaps *termcaps)
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
//changer la fonction car si plusieurs lignes part en couille

void	print_highlight(t_termcaps *termcaps, char *cmd)
{
	int i;
	int y;

	i = 0;
	y = 0;
	del_line(termcaps);
	display_name();
	ft_bzero(termcaps->tmp_select, NAME_MAX);
	while (i < termcaps->cc_start && i < termcaps->pos)
	{
		ft_putchar(cmd[i]);
		i++;
	}
	highlight(termcaps);
	while (i <= bigger(termcaps->cc_start, termcaps->pos))
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
**
** On va enlever de cmd la partie qui se trouve entre "pos" et "cc_start"
** En fonction du sens de selection pos peut etre avant ou apres start.
**		Cela est gere par la condition
** On va malloc la taille totale moins celle de la string selectionnee
** On copie dans new_cmd jusqu'a arriver au curseur
** On continue dans la string sans copier jusqu'a la fin du curseur
** Ensuite on continue a copier
** On free la commande qu'on a remplace
*/

void		cut_in_cmd(t_termcaps *t, char **cmd)
{
	int		i;
	int		y;
	char	*new_cmd;
	char	*tmp;

	tmp = *cmd;
	i = 0;
	y = 0;
	new_cmd = ft_strnew(t->cmd_len - val_abs(t->pos - t->cc_start));
	if (t->pos > t->cc_start)
	{
		while (i < t->cc_start)
			new_cmd[y++] = (*cmd)[i++];
		while (i <= t->pos)
			i++;
	}
	else
	{
		while (i < t->pos)
			new_cmd[y++] = (*cmd)[i++];
		while (i <= t->cc_start)
			i++;
	}
	while ((*cmd)[i])
		new_cmd[y++] = (*cmd)[i++];
	ft_strdel(&tmp);
	*cmd = ft_strdup(new_cmd);
	ft_strdel(&new_cmd);
}
