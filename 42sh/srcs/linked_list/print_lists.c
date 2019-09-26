/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lists.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcedric <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 12:38:21 by bcedric           #+#    #+#             */
/*   Updated: 2019/06/24 12:38:23 by bcedric          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		print_handled_token_list(t_handled_token *tokens)
{
	int size;

	size = 0;
	while (tokens)
	{
		size++;
		ft_printf("{green}value: \
			%s\nname: %d\npriority: %d\n---------------\n{eoc}",
			tokens->value, tokens->name, tokens->priority);
		tokens = tokens->next;
	}
	ft_printf("----------------\nTaille de la liste: %d\n", size);
}

void		print_history(t_history *history)
{
	int			i;
	t_history	*tmp;

	i = 0;
	ft_printf("-----\n");
	tmp = history;
	while (history != NULL)
	{
		i++;
		ft_printf("%d.  %s\n", i, history->opening);
		history = history->next;
	}
	history = tmp;
	ft_printf("-----\n\n");
}

void		print_token_list(t_token *tokens)
{
	int size;

	size = 0;
	while (tokens)
	{
		size++;
		ft_printf("{cyan}value: %s\n{eoc}",
			tokens->value);
		ft_printf("{cyan}priority: %d\nname:"
			"%d\n------------------------\n{eoc}",
			tokens->priority, tokens->name);
		if (tokens->next == NULL)
			break ;
		tokens = tokens->next;
	}
	ft_printf("----------------\nTaille de la liste: %d\n", size);
}
