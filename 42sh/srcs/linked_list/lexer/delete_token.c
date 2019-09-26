/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjovanov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 15:26:03 by bjovanov          #+#    #+#             */
/*   Updated: 2019/05/13 15:26:04 by bjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void			delete_token(t_token **tokens, t_token **begin)
{
	t_token *tmp;
	t_token *prev;
	t_token *next;

	tmp = *tokens;
	prev = tmp->prev;
	next = tmp->next;
	if (token_lst_len(*tokens) >= 1)
	{
		if (prev)
			prev->next = next;
		else
			*begin = next;
		if (next)
			next->prev = prev;
	}
	ft_strdel(&(tmp->value));
	free(tmp);
}

void			delete_token_list(t_token **tokens)
{
	t_token	*next;

	if (*tokens == NULL)
		return ;
	while ((*tokens)->prev != NULL)
		(*tokens) = (*tokens)->prev;
	while ((*tokens))
	{
		next = (*tokens)->next;
		ft_strdel(&((*tokens)->value));
		free(*tokens);
		*tokens = next;
	}
	tokens = NULL;
}
