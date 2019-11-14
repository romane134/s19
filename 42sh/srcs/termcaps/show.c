/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 15:05:03 by sstinglh          #+#    #+#             */
/*   Updated: 2019/07/17 17:39:30 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char		*get_dirpath(void)
{
	char *path;
	char *dir;

	if ((path = getcwd(NULL, 0)) == NULL)
		return (ft_strdup(""));
	if ((dir = ft_strdup(strrchr(path, '/') + 1)) == NULL)
		exit(EXIT_FAILURE);
	if (ft_strequ(dir, ""))
	{
		ft_strdel(&dir);
		if ((dir = ft_strdup("/")) == NULL)
			exit(EXIT_FAILURE);
	}
	ft_strdel(&path);
	return (dir);
}

void		print_research_result(char *cmd, t_termcaps *termcaps)
{
	int len_cmd;

	if ((int)ft_strlen(cmd) > termcaps->size)
	{
		len_cmd = (int)ft_strlen(cmd);
		while (len_cmd > termcaps->size)
		{
			tputs(tgoto(termcaps->godown, 0, 0), 1, (void *)ft_putchar);
			tputs(termcaps->del_allline, 1, (void *)ft_putchar);
			len_cmd -= termcaps->size;
		}
	}
	ft_printf("%s\n", cmd);
}

void		print_research_mode(t_termcaps *termcaps, char **cmd, int *height)
{
	int		nbre_len1;
	int		nbre_len2;
	char	*cmd_look;

	nbre_len1 = ((termcaps->prev_cmd + display_name_len() - 1) /
	(termcaps->size));
	nbre_len2 = ((14 + termcaps->prev_pos) / termcaps->size);
	*height = nbre_len1 + nbre_len2 + 1;
	while ((*height) > 0)
	{
		tputs(tgoto(termcaps->goup, 0, 0), 1, (void *)ft_putchar);
		(*height)--;
	}
	tputs(tgoto(termcaps->gostart, 0, 0), 1, (void *)ft_putchar);
	tputs(termcaps->del_allline, 1, (void *)ft_putchar);
	cmd_look = result_reasearch(*cmd, termcaps);
	display_name();
	if (cmd_look)
		print_research_result(cmd_look, termcaps);
	else
		ft_putchar('\n');
	ft_strdel(&cmd_look);
	termcaps->prev_cmd = ft_strlen(*cmd);
	termcaps->display_option = 123;
}

void		print_no_r(int *height, t_termcaps *termcaps)
{
	int		y;

	y = ((termcaps->prev_pos + termcaps->path) / termcaps->size);
	*height = ((termcaps->cmd_len + termcaps->path) / termcaps->size);
	while (y-- > 0)
		tputs(tgoto(termcaps->goup, 0, 0), 1, (void *)ft_putchar);
	tputs(tgoto(termcaps->gostart, 0, 0), 1, (void *)ft_putchar);
	tputs(termcaps->del_allline, 1, (void *)ft_putchar);
}

void		print_new(char *cmd, t_termcaps *termcaps, int opt_save)
{
	int		height;

	termcaps->research_mode ? print_research_mode(termcaps, &cmd, &height)
	: print_no_r(&height, termcaps);
	choose_display(termcaps);
	if (termcaps->edit_mode == 1)
		print_highlight(termcaps, cmd);
	else
		ft_putstr(cmd);
	termcaps->height = height;
	if ((termcaps->cmd_len + termcaps->path) % termcaps->size == 0)
		tputs(tgoto(termcaps->godown, 0, 0), 1, (void *)ft_putchar);
	if (opt_save != 0)
		term_reset(termcaps);
	termcaps->prev_pos = termcaps->pos;
}
