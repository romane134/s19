/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstinglh <sstinglh@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 13:58:52 by sstinglh          #+#    #+#             */
/*   Updated: 2019/06/27 15:39:03 by sstinglh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	end_key(t_termcaps *t)
{
	int i;

	i = (t->pos + t->path) % t->size;
	while ((t->pos + t->path) / t->size < (t->cmd_len + t->path) / t->size)
	{
		i = 0;
		tputs(tgoto(t->godown, 0, 0), 1, (void *)ft_putchar);
		t->pos += t->size;
	}
	while (i++ < (t->cmd_len + t->path) % t->size)
		tputs(tgoto(t->goright, 0, 0), 1, (void *)ft_putchar);
	t->pos = t->cmd_len;
}

void	home_key(t_termcaps *t, char **cmd)
{
	while ((t->pos) / t->size > 0)
	{
		tputs(tgoto(t->goup, 0, 0), 1, (void *)ft_putchar);
		t->pos -= t->size;
	}
	while (t->pos > 0)
		go_left(t, cmd);
	while (t->pos < 0)
		go_right(t, cmd);
	t->pos = 0;
}

void	arrow_key(char *buffer, t_termcaps *t, char **cmd)
{
	if (buffer[2] == ARROW_LEFT && t->pos > 0)
		left_key(t, cmd);
	else if (buffer[2] == ARROW_RIGHT && t->pos < t->cmd_len)
		right_key(t, cmd);
	else if (buffer[2] == ARROW_UP || buffer[2] == ARROW_DOWN)
		termcaps_histo(t, cmd, buffer[2]);
	else if (buffer[2] == HOME)
		home_key(t, cmd);
	else if (buffer[2] == END)
		end_key(t);
	else if (buffer[2] == MAJ)
		maj_combi(t, *cmd, buffer);
}

void	key_tab(char **cmd, t_termcaps *termcaps)
{
	char	*tmp;
	int		old_cmd_len;

	old_cmd_len = ft_strlen(*cmd);
	tmp = *cmd;
	termcaps->edit_mode = FALSE;
	*cmd = autocomplete(tmp, termcaps);
	termcaps->cmd_len = ft_strlen(*cmd);
	termcaps->pos += ft_strlen(*cmd) - old_cmd_len;
	ft_strdel(&tmp);
	print_new(*cmd, termcaps, 1);
}

void	backspace_key(char **cmd, t_termcaps *termcaps)
{
	termcaps->edit_mode = FALSE;
	if (termcaps->pos > 0)
	{
		*cmd = remove_previous_char(*cmd, termcaps);
		termcaps->pos--;
		termcaps->cmd_len--;
		print_new(*cmd, termcaps, 2);
	}
}
