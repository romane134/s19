/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 11:04:23 by smondesi          #+#    #+#             */
/*   Updated: 2019/07/06 15:20:54 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		ast_left(t_token *li)
{
	int		i;
	t_token *tmp;
	t_token *start;

	i = li->priority + 1;
	start = li;
	if (li->prev == NULL || li->prev->priority < i - 1)
	{
		li->left = NULL;
		return ;
	}
	while (li->prev != NULL && li->prev->priority >= i)
		li = li->prev;
	tmp = li;
	while (li->priority != i)
	{
		if ((li = li->next) == NULL || li == start)
		{
			li = tmp;
			i++;
		}
	}
	start->left = li;
	ast_right(li);
	ast_left(li);
}

void		ast_right(t_token *li)
{
	int		i;
	t_token *tmp;

	i = li->priority;
	if (li->next == NULL || li->next->priority < i)
	{
		li->right = NULL;
		return ;
	}
	li = li->next;
	tmp = li;
	while (li->priority != i)
	{
		if ((li = li->next) == NULL || li->priority < i)
		{
			li = tmp;
			i++;
		}
	}
	tmp->prev->right = li;
	ast_right(li);
	ast_left(li);
}

t_token		*ast_start(t_token *li)
{
	int			i;
	t_token		*tmp;

	i = -1;
	tmp = li;
	while (li->priority != i)
		if ((li = li->next) == NULL)
		{
			li = tmp;
			i++;
		}
	ast_right(li);
	ast_left(li);
	return (li);
}

t_token		*parseur(t_token *list)
{
	list = ast_start(list);
	return (list);
}
