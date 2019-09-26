/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token_item.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 15:25:16 by bjovanov          #+#    #+#             */
/*   Updated: 2019/07/02 22:34:09 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void			add_token(t_token **tokens, char *value, enum e_tokens name,
			int priority)
{
	t_token *new;
	t_token *tmp;

	if (!(new = malloc(sizeof(*new))))
		exit_shell_code("malloc error", MALLOC_FAILURE);
	if (!(new->value = value))
		exit_shell_code("malloc error", MALLOC_FAILURE);
	new->name = name;
	new->priority = priority;
	new->left = NULL;
	new->right = NULL;
	new->parent = NULL;
	if (*tokens == NULL)
	{
		new->next = NULL;
		new->prev = NULL;
		*tokens = new;
		return ;
	}
	tmp = *tokens;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->next = NULL;
	new->prev = tmp;
}

void			add_front_token(t_token **tokens, char *value,
						enum e_tokens name, int priority)
{
	t_token *new;

	if (!(new = malloc(sizeof(*new))))
		exit_shell_code("malloc error", MALLOC_FAILURE);
	if (!(new->value = value))
		exit_shell_code("malloc error", MALLOC_FAILURE);
	new->name = name;
	new->priority = priority;
	new->left = NULL;
	new->right = NULL;
	new->parent = NULL;
	if (*tokens == NULL)
	{
		new->next = NULL;
		new->prev = NULL;
		*tokens = new;
		return ;
	}
	new->next = *tokens;
	new->prev = NULL;
	(*tokens)->prev = new;
	*tokens = new;
}
