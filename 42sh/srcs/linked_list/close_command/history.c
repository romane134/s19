/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 14:29:53 by vjovanov          #+#    #+#             */
/*   Updated: 2019/07/02 22:33:52 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		add_history(t_history **history, char *opening, char *closing)
{
	t_history *item;
	t_history *tmp;

	tmp = *history;
	if (!(item = malloc(sizeof(*item))))
		exit_shell_code("malloc error", MALLOC_FAILURE);
	if (!(item->opening = ft_strdup(opening)))
		exit_shell_code("malloc error", MALLOC_FAILURE);
	if (!(item->closing = ft_strdup(closing)))
		exit_shell_code("malloc error", MALLOC_FAILURE);
	item->next = NULL;
	if (*history == NULL)
	{
		*history = item;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = item;
}

void		remove_last_history(t_history **history)
{
	t_history *tmp;
	t_history *beforelast;

	tmp = *history;
	beforelast = NULL;
	if (*history == NULL)
		return ;
	if ((*history)->next == NULL)
	{
		ft_strdel(&((*history)->opening));
		ft_strdel(&((*history)->closing));
		free(*history);
		*history = NULL;
		return ;
	}
	while (tmp->next != NULL)
	{
		beforelast = tmp;
		tmp = tmp->next;
	}
	beforelast->next = NULL;
	ft_strdel(&(tmp->opening));
	ft_strdel(&(tmp->closing));
	free(tmp);
	tmp = NULL;
}

const char	*get_last_history_opening(t_history *history)
{
	t_history *last_element;
	t_history *begin;

	if (history == NULL)
		return (NULL);
	begin = history;
	while (history->next != NULL)
		history = history->next;
	last_element = history;
	history = begin;
	return (last_element->opening);
}

const char	*get_last_history_closing(t_history *history)
{
	t_history *last_element;
	t_history *begin;

	if (history == NULL)
		return (NULL);
	begin = history;
	while (history->next != NULL)
		history = history->next;
	last_element = history;
	history = begin;
	return (last_element->closing);
}
