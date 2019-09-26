/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 11:29:52 by vjovanov          #+#    #+#             */
/*   Updated: 2019/07/22 16:29:39 by bjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		restart(char **line, t_history *history, t_termcaps *termcaps)
{
	char		*readl;
	char		*tmp;
	const char	*last;
	int			lastchar;

	last = get_last_history_opening(history);
	readl = termcaps_main(termcaps, 2);
	if (g_shell->stop == 1)
	{
		ft_strdel(line);
		ft_strdel(&readl);
		return ;
	}
	lastchar = 0;
	while (ft_isspace((*line)[ft_strlen(*line) - 1 - lastchar]))
		lastchar++;
	if (!(tmp = ft_str3join(*line, "\n", readl)))
		exit_shell_code("malloc error", MALLOC_FAILURE);
	ft_strdel(line);
	ft_strdel(&readl);
	*line = tmp;
}

int			check_is_opening_token(char *line, int i, t_history **history)
{
	t_handled_token *tmp;

	tmp = g_shell->handled_token;
	if (ft_strequ(get_last_history_opening(*history), "'"))
		return (0);
	while (tmp != NULL)
	{
		if (ft_strnequ(&(line[i]), tmp->value, ft_strlen(tmp->value)))
		{
			if (tmp->closing == NULL ||
				(count_backslashes(line, i - (i == 0 ? 0 : 1)) % 2 == 1)
				|| (!ft_strequ(tmp->value, "${") &&
					ft_strequ(get_last_history_opening(*history), "\"")))
				return ((int)ft_strlen(tmp->value) - 1);
			add_history(history, tmp->value, tmp->closing);
			return ((int)ft_strlen(tmp->value) - 1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void		free_history(t_history **history)
{
	t_history *tmp;

	if (*history == NULL)
		return ;
	tmp = NULL;
	while (*history != NULL)
	{
		ft_strdel(&((*history)->opening));
		ft_strdel(&((*history)->closing));
		tmp = *history;
		*history = (*history)->next;
		free(tmp);
		tmp = NULL;
	}
}

int			check_line(char **line, t_history *history, t_termcaps *t)
{
	restart(line, history, t);
	free_history(&history);
	if (g_shell->stop == 1)
		return (1);
	close_command(line, t);
	return (0);
}

void		close_command(char **line, t_termcaps *termcaps)
{
	t_history			*history;
	const char			*closing;
	int					i;

	i = -1;
	history = NULL;
	if (*line == NULL || line == NULL)
		return ;
	while (line[0][++i])
	{
		closing = get_last_history_closing(history);
		if (ft_strnequ(&(line[0][i]), closing, closing ? ft_strlen(closing) : 0)
			&& !is_escaped(line[0], i))
		{
			remove_last_history(&history);
			continue ;
		}
		i += check_is_opening_token(*line, i, &history);
	}
	if (history != NULL && check_line(line, history, termcaps))
		return ;
}
