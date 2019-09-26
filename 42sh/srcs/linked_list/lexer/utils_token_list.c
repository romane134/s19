/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 15:27:14 by bjovanov          #+#    #+#             */
/*   Updated: 2019/07/22 14:36:47 by bjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int				token_lst_len(t_token *token)
{
	int size;

	size = 0;
	if (token == NULL)
		return (0);
	while (token)
	{
		size++;
		token = token->next;
	}
	return (size);
}

int				is_token(char *token)
{
	t_handled_token	*tmp;

	tmp = g_shell->handled_token;
	while (tmp != NULL)
	{
		if (ft_strnequ(token, tmp->value, ft_strlen(tmp->value)))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

t_handled_token	*is_closing_token(char *line, int i)
{
	t_handled_token *tmp;

	tmp = g_shell->handled_token;
	if (count_backslashes(line, i - ((i == 0) ? 0 : 1)) % 2 != 0)
		return (NULL);
	while (tmp)
	{
		if (ft_strnequ(&(line[i]), tmp->value, ft_strlen(tmp->value)) &&
			tmp->closing != NULL)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

t_handled_token	*is_splitter_token(char *line, int i)
{
	t_handled_token *tmp;

	tmp = g_shell->handled_token;
	if (count_backslashes(line, i - ((i == 0) ? 0 : 1)) % 2 != 0)
		return (NULL);
	while (tmp)
	{
		if (ft_strnequ(&(line[i]), tmp->value, ft_strlen(tmp->value)) &&
			tmp->splitter == 1)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}
