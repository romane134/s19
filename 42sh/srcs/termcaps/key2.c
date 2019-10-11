/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstinglh <sstinglh@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 14:37:42 by sstinglh          #+#    #+#             */
/*   Updated: 2019/08/01 23:56:10 by sstinglh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
** del_key()
** Touche "del"
** On quitte le mode edit
** Si on n'est pas au dernier caractere
** on remove le char suivant avec remove_next_char()
** On reprint
** On reduit la cmd_len
*/

void	del_key(char **cmd, t_termcaps *termcaps)
{
	termcaps->edit_mode = FALSE;
	if (termcaps->pos < termcaps->cmd_len)
	{
		*cmd = remove_next_char(*cmd, termcaps);
		show_new(*cmd, termcaps, 1);
		termcaps->cmd_len--;
	}
}
/*
** au moment ou on appuie sur enter
**
*/
char	*entre_key(t_termcaps *t, char *cmd, char **buffer)
{
	t->edit_mode = FALSE;
	ft_strdel(buffer);
	if (expansion_history(&cmd))
		add_in_history(t, cmd);
	tputs(tgoto(t->godown, 0, 0), 1, (void *)ft_putchar); //descendre d'ue ligne
	tputs(tgoto(t->gostart, 0, 0), 1, (void *)ft_putchar); // ?
	if (tcsetattr(0, TCSADRAIN, &t->term_restore) == -1)
		exit(-1);
	return (cmd);
}

void	maj_right(t_termcaps *t, char *cmd)
{
	while (cmd[t->pos] == ' ' && t->pos < (int)t->cmd_len)
	{
		go_right(t, &cmd);
		if ((t->pos + t->path) % t->size == 0)
			tputs(tgoto(t->godown, 0, 0), 1, (void *)ft_putchar);
	}
	while (cmd[t->pos] != ' ' && t->pos < (int)t->cmd_len)
	{
		go_right(t, &cmd);
		if ((t->pos + t->path) % t->size == 0)
			tputs(tgoto(t->godown, 0, 0), 1, (void *)ft_putchar);
	}
}

void	maj_combi(t_termcaps *t, char *cmd, char *buffer)
{
	read(0, buffer, 3);
	if (!ft_strcmp(buffer, MAJ_LEFT) && t->pos > 0)
	{
		while (cmd[t->pos] == ' ' && t->pos > 0)
			go_left(t, &cmd);
		while (cmd[t->pos] != ' ' && t->pos > 0)
			go_left(t, &cmd);
	}
	else if (!ft_strcmp(buffer, MAJ_RIGHT))
		maj_right(t, cmd);
	else if (!ft_strcmp(buffer, MAJ_UP) && t->pos - t->size > 0)
	{
		tputs(tgoto(t->goup, 0, 0), 1, (void *)ft_putchar);
		t->pos = t->pos - t->size;
	}
	else if (!ft_strcmp(buffer, MAJ_DOWN) && t->pos + t->size < t->cmd_len)
		down_one_line(t);
}

void	alt_maj(t_termcaps *termcaps, char **cmd, char *buffer)
{
	if (buffer[0] == CTRL_MAJ_E_1 && buffer[1] == CTRL_MAJ_E_2)
	{
		termcaps->cc_start = 0;
		termcaps->cc_start = termcaps->pos;
		termcaps->edit_mode = !termcaps->edit_mode;
		show_new(*cmd, termcaps, 1);
	}
	else if (buffer[0] == CTRL_MAJ_C_1 && buffer[1] == CTRL_MAJ_C_2)
	{
		if (termcaps->edit_mode)
			termcaps->copy = ft_strdup(termcaps->tmp_select);
	}
	else if (buffer[0] == CTRL_MAJ_X_1 && buffer[1] == CTRL_MAJ_X_2)
		cut(termcaps, cmd);
	else if (buffer[0] == CTRL_MAJ_V_1 && buffer[1] == CTRL_MAJ_V_2)
		paste(termcaps, cmd);
}
