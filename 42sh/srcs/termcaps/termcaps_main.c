/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smondesi <smondesi@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 12:07:55 by smondesi          #+#    #+#             */
/*   Updated: 2019/08/01 22:37:33 by sstinglh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
** term_reset()
** => Remet le curseur a la bonne position
** y = hauteur ou on se trouve
** height = hauteur
** while (i < (height - y)) On remonte les lignes jusqu'a celle de la position
** while (i < x) on se replace sur la ligne en x
*/

void			term_reset(t_termcaps *termcaps)
{
	int x;
	int y;
	int i;
	int	height;

	i = 0;
	y = ((termcaps->pos + termcaps->path) / termcaps->size);
	x = (termcaps->pos + termcaps->path) % termcaps->size;
	height = ((termcaps->cmd_len + termcaps->path) / termcaps->size);
	tputs(tgoto(termcaps->gostart, 0, 0), 1, (void *)ft_putchar);
	while (i < (height - y))
	{
		i++;
		tputs(tgoto(termcaps->goup, 0, 0), 1, (void *)ft_putchar);
	}
	i = 0;
	while (i < x)
	{
		i++;
		tputs(tgoto(termcaps->goright, 0, 0), 1, (void *)ft_putchar);
	}
}

void			just_char(t_termcaps **t, char **cmd, char **buffer)
{
	(*t)->edit_mode = FALSE;
	((*t)->pos == (int)ft_strlen(*cmd)) ?
	add_char_end(cmd, *buffer) : add_char(cmd, *buffer, *t);
	(*t)->pos += ft_strlen(*buffer);
	(*t)->cmd_len += ft_strlen(*buffer);
	print_new(*cmd, *t, 1);
}

void			which_key(char **buffer, char **cmd, t_termcaps **t)
{
	if ((*buffer)[0] == '\n' && ((*buffer)[1] != '\n' || (*buffer)[2] != '\n'))
		remove_backn(buffer);
	if ((*buffer)[0] == CTRL_D && *cmd[0] == '\0')
	{
		tcsetattr(0, 0, &(*t)->term_restore);
		builtin_exit(NULL, NULL);
	}
	else if ((*buffer)[0] == CTRL_R)
	{
		(*t)->research_mode = 1;
		if ((*t)->r_hist > 0)
			(*t)->r_hist--;
		print_new(*cmd, *t, 1);
	}
	else if ((*buffer)[0] == TAB && (*buffer)[1] == 0)
		key_tab(cmd, *t);
	else if ((*buffer)[0] == ARROW_1 && (*buffer)[1] == ARROW_2)
		arrow_key(*buffer, *t, cmd);
	else if ((*buffer)[0] == BACKSPACE)
		backspace_key(cmd, *t);
	else if ((*buffer)[0] == -62 || (*buffer)[0] == -61 || (*buffer)[0] == -53
	|| (*buffer)[0] == -30)
		alt_maj(*t, cmd, *buffer);
	else if (isprintable(*buffer) || (*buffer)[0] == '\n')
		just_char(t, cmd, buffer);
}

static void		term_sig(char **cmd, t_termcaps *termcaps)
{
	if (g_shell->stop == 1)
		reset_stdin();
	win_change_handler(SIGWINCH);
	if (g_shell->i == 1)
		ctrl_c(termcaps, cmd);
}

char			*termcaps_main(t_termcaps *termcaps, int opt_display)
{
	char	*buffer;
	char	*cmd;

	init_new_cmd(termcaps, opt_display, &cmd);
	buffer = ft_strnew(3);
	while (1)
	{
		if (cmd == NULL)
			cmd = ft_strnew(0);
		read(0, buffer, 3);
		term_sig(&cmd, termcaps);
		if (buffer[0] == ENTER && ((buffer[1] == '\n' ||
		!buffer[1]) && (buffer[2] == '\n' || !buffer[2])))
		{
			if (termcaps->research_mode == FALSE)
				return (entre_key(termcaps, cmd, &buffer));
			reasearch_key(&cmd, termcaps);
		}
		else
			which_key(&buffer, &cmd, &termcaps);
		termcaps->prev_pos = termcaps->pos;
		ft_bzero(buffer, 3);
	}
}
