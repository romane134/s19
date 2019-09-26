/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstinglh <sstinglh@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 13:58:26 by sstinglh          #+#    #+#             */
/*   Updated: 2019/08/29 17:38:26 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
** Met le terminal en mode canonique
** 	les touches tapees ne s'inscriront plus dans le terminal
*/

void		print_shell_usage(t_termcaps *termcaps)
{
	tputs(tparm(termcaps->text_color, COLOR_MAGENTA), 1, (void *)ft_putchar);
	ft_printf("------Welcome on %s !------\n\n", SHELL_NAME);
	ft_printf("ALT + MAJ + E : Edit mode\n");
	ft_printf("ALT + MAJ + C : Copy\n");
	ft_printf("ALT + MAJ + V : Paste\n");
	ft_printf("ALT + MAJ + X : Cut\n");
	ft_printf("MAJ + LEFT    : Previous word\n");
	ft_printf("MAJ + RIGHT   : Next word\n");
	ft_printf("MAJ + UP      : Upper line\n");
	ft_printf("MAJ + DOWN    : Downer line\n");
	reset_highlight(termcaps);
}

int			term_init(t_termcaps *termcaps)
{
	char	*name_term;

	if ((name_term = getenv("TERM")) == NULL)
		exit(-1);
	if (tgetent(NULL, name_term) == -1)
		exit(-1);
	if (tcgetattr(0, &termcaps->term) == -1)
		exit(-1);
	termcaps->term.c_lflag &= ~(ICANON | ECHO);
	termcaps->term.c_cc[VMIN] = 1;
	termcaps->term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, &termcaps->term) == -1)
		exit(-1);
	get_termcaps(termcaps);
	if (open_history_file(termcaps) == -1)
		exit(-1);
	termcaps->tmp_select = ft_strnew(0);
	print_shell_usage(termcaps);
	return (0);
}

void		init_new_cmd(t_termcaps *termcaps, int opt_display)
{
	termcaps->pos = 0;
	termcaps->pos_line = 0;
	termcaps->history_pos = 0;
	termcaps->cmd_len = 0;
	termcaps->edit_mode = FALSE;
	termcaps->height = 0;
	termcaps->prev_pos = 0;
	termcaps->research_mode = 0;
	termcaps->r_hist = termcaps->history_len;
	if (tcsetattr(0, TCSADRAIN, &termcaps->term) == -1)
		exit(-1);
	termcaps->display_option = opt_display;
	choose_display(termcaps);
}

void		get_termcaps(t_termcaps *termcaps)
{
	termcaps->gotostr = tgetstr("cm", NULL);
	termcaps->goleft = tgetstr("le", NULL);
	termcaps->goright = tgetstr("nd", NULL);
	termcaps->godown = tgetstr("do", NULL);
	termcaps->goup = tgetstr("up", NULL);
	termcaps->gostart = tgetstr("cr", NULL);
	termcaps->clearstr = tgetstr("cl", NULL);
	termcaps->del_line = tgetstr("dl", NULL);
	termcaps->del_allline = tgetstr("cd", NULL);
	termcaps->curs_save = tgetstr("sc", NULL);
	termcaps->curs_restore = tgetstr("rc", NULL);
	termcaps->highlight_color = tgetstr("AB", NULL);
	termcaps->reset = tgetstr("me", NULL);
	termcaps->text_color = tgetstr("AF", NULL);
}
