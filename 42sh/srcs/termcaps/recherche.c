/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recherche.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstinglh <sstinglh@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 17:54:46 by sstinglh          #+#    #+#             */
/*   Updated: 2019/08/29 17:22:12 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
** rechercher dans l'historique la commande la plus proche de old_cmd
*/

int		prepare_read_history_line_by_line(void)
{
	char	*history_path;
	char	*line;
	int		fd;

	line = NULL;
	history_path = ft_strjoin(getenv("HOME"), "/.42sh_history");
	if ((fd = open(history_path, O_RDWR | O_CREAT | O_APPEND,
					0777)) == -1)
	{
		ft_strdel(&history_path);
		return (0);
	}
	ft_strdel(&history_path);
	get_next_line(fd, NULL, 1);
	return (fd);
}

char	*result_reasearch(char *old_cmd, t_termcaps *t)
{
	char	*result;
	char	*line;
	size_t	i[2];
	int		fd;

	i[0] = -1;
	i[1] = 0;
	if ((fd = prepare_read_history_line_by_line()) == -1)
		return (NULL);
	line = NULL;
	result = ft_strnew(0);
	while (++i[0] <= t->r_hist)
	{
		if (get_next_line(fd, &line, 0) != 0)
			if (ft_strlen(old_cmd) != 0 && ft_strstr(line, old_cmd) != NULL)
			{
				ft_strdel(&result);
				result = ft_strdup(line);
				i[1] = i[0];
			}
		ft_strdel(&line);
	}
	t->r_hist = i[1] > 0 ? i[1] + 1 : t->r_hist;
	close(fd);
	return (result);
}

char	*result_reasearch_without_termcaps(char *old_cmd)
{
	char	*result;
	char	*line;
	size_t	i;
	int		fd;

	i = get_history_len();
	if ((fd = prepare_read_history_line_by_line()) == -1)
		return (NULL);
	line = NULL;
	result = NULL;
	while (i--)
	{
		get_next_line(fd, &line, 0);
		if (ft_strlen(old_cmd) != 0 && ft_strstr(line, old_cmd) != NULL)
		{
			ft_strdel(&result);
			result = ft_strdup(line);
		}
		ft_strdel(&line);
	}
	close(fd);
	return (result);
}

void	reasearch_key(char **cmd, t_termcaps *termcaps)
{
	char *tmp;

	termcaps->research_mode = !termcaps->research_mode;
	termcaps->display_option = 1;
	termcaps->pos = 0;
	tputs(tgoto(termcaps->goup, 0, 0), 1, (void *)ft_putchar);
	tputs(tgoto(termcaps->gostart, 0, 0), 1, (void *)ft_putchar);
	termcaps->cmd_len = 0;
	g_shell->i = 0;
	tmp = (*cmd);
	(*cmd) = result_reasearch(tmp, termcaps);
	ft_strdel(&tmp);
	print_new(*cmd, termcaps, 1);
}
