/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_paste.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstinglh <sstinglh@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 13:54:37 by sstinglh          #+#    #+#             */
/*   Updated: 2019/06/27 14:57:12 by sstinglh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
** cut()
** Si on est en edit mode, on va mettre dans cmd la commande en retirant ce
** 	qui est selectionne (cf cut_in_cmd())
** On place dans termcaps->copy ce qui est selectionne
** On reaffiche la nouvelle cmd
** On replace le curseur au bon endroit
** On redefini la taille de la commande
** On quitte le mode d'edition
*/

void	cut(t_termcaps *termcaps, char **cmd)
{
	if (termcaps->edit_mode)
	{
		cut_in_cmd(termcaps, cmd);
		ft_strcpy(termcaps->copy, termcaps->tmp_select);
		termcaps->edit_mode = FALSE;
		if (termcaps->cc_start < termcaps->pos)
			termcaps->pos -= ft_strlen(termcaps->copy);
		termcaps->cmd_len -= ft_strlen(termcaps->tmp_select);
		show_new(*cmd, termcaps, 1);
	}
}

/*
** paste()
** Si il y a qq chose dans termcaps->copy, on va l'ajouter a la cmd avec
**< add_char()
** On rajoute a pos et cmd_len la taille de la string copiee
** On deplace le curseur de la taille de la string collee
*/

void	paste(t_termcaps *termcaps, char **cmd)
{
	if (termcaps->copy[0])
	{
		dprintf(debug(), "cpy : |%s|\n", termcaps->copy);
		add_char(cmd, termcaps->copy, termcaps);
		termcaps->pos += ft_strlen(termcaps->copy);
		termcaps->cmd_len += ft_strlen(termcaps->copy);
		show_new(*cmd, termcaps, 1);
		termcaps->edit_mode = FALSE;
	}
}
