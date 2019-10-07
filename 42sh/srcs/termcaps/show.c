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

char	*get_dirpath(void)
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

int		display_name(void)
{
	char	*dir;
	int		len_dir;

	if (!(dir = get_dirpath()))
		exit_shell_code("malloc error", MALLOC_FAILURE);
	len_dir = ft_strlen(dir);
	//if (ft_strlen(g_shell->pwd->pwd) != 1 && g_shell->pwd->pwd
	//  [ft_strlen(g_shell->pwd->pwd) - 1] == '/')
	//	g_shell->pwd->pwd[ft_strlen(g_shell->pwd->pwd) - 1] = '\0';
	ft_putstr("\033[93m");
	ft_putstr(dir);
	ft_putstr(" > ");
	ft_putstr("\033[0m");
	ft_strdel(&dir);
	return (len_dir + 3);
}

int		display_name_len(void)
{
	if (g_shell->pwd->pwd[ft_strlen(g_shell->pwd->pwd) - 1] == '/')
		g_shell->pwd->pwd[ft_strlen(g_shell->pwd->pwd) - 1] = '\0';
	return (ft_strlen(g_shell->pwd->pwd) + 3);
}

int		only_arrow(void)
{
	ft_putstr("\033[93m");
	ft_putstr(" > ");
	ft_putstr("\033[0m");
	return (3);
}

int		ft_reasearch_prompt(void)
{
	ft_putstr("\033[93m");
	ft_putstr("reasearch_MTF ");
	ft_putstr("\033[0m");
	return (14);
}

void	choose_display(t_termcaps *termcaps)
{
	if (termcaps->display_option == 1)
		termcaps->path = display_name();
	else if (termcaps->display_option == 2)
		termcaps->path = only_arrow();
	else
		termcaps->path = ft_reasearch_prompt();
}

// char	*result_reasearch(char *old_cmd)
// {
// 	// ft_strdel(&old_cmd);
// 	// old_cmd = ft_strdup("coucou");
// 	return (old_cmd);
// 	// return (ft_strdup("coucou"));
// }
//
// /*
// ** show_new()
// ** y = hauteur ou l'on se trouve
// ** height = hauteur de la cmd dans le shell
// ** while(y > 0) on remonte en haut pour effacer les lignes en dessous
// */

void	show_new(char *cmd, t_termcaps *termcaps, int opt_save)
{
	int		y;
	int		height;
	char	*cmd_look;
	int		nbre_len1;
	int		nbre_len2;

	nbre_len1 = 0;
	nbre_len2 = 0;
	y = 0;
	height = 0;
	if (termcaps->research_mode)
	{
		nbre_len1 = ((termcaps->prev_cmd + display_name_len() - 1) /
		(termcaps->size));
		nbre_len2 = ((14 + termcaps->prev_pos) / termcaps->size);
		height = nbre_len1 + nbre_len2 + 1;
		while (height-- > 0)
			tputs(tgoto(termcaps->goup, 0, 0), 1, (void *)ft_putchar);
		tputs(tgoto(termcaps->gostart, 0, 0), 1, (void *)ft_putchar);
		tputs(tgoto(termcaps->del_allline, 0, 0), 1, (void *)ft_putchar);
		cmd_look = result_reasearch(cmd, termcaps);
		display_name();
		if (cmd_look)
			ft_printf("%s\n", cmd_look);
		else
			ft_putchar('\n');
		ft_strdel(&cmd_look);
		termcaps->prev_cmd = ft_strlen(cmd);
		termcaps->display_option = 123;
	}
	else
	{
		y = ((termcaps->prev_pos + termcaps->path) / termcaps->size);
		height = ((termcaps->cmd_len + termcaps->path) / termcaps->size);
		while (y-- > 0)
			tputs(tgoto(termcaps->goup, 0, 0), 1, (void *)ft_putchar);
		tputs(tgoto(termcaps->gostart, 0, 0), 1, (void *)ft_putchar);
		tputs(termcaps->del_allline, 1, (void *)ft_putchar);
	}
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
	// termcaps->prev_cmd = termcaps->cmd_len;
	// ft_printf("%d | %d", nbre_len1, nbre_len2);
}
