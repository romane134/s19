/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handled_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 15:41:39 by bjovanov          #+#    #+#             */
/*   Updated: 2019/07/02 22:34:06 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static char	*get_closing(char *value)
{
	char *closing;

	closing = NULL;
	if (ft_strequ(value, "${"))
	{
		if (!(closing = ft_strdup("}")))
			exit_shell_code("malloc error", MALLOC_FAILURE);
		return (closing);
	}
	if (ft_strequ(value, "\""))
	{
		if (!(closing = ft_strdup("\"")))
			exit_shell_code("malloc error", MALLOC_FAILURE);
		return (closing);
	}
	if (ft_strequ(value, "'"))
	{
		if (!(closing = ft_strdup("'")))
			exit_shell_code("malloc error", MALLOC_FAILURE);
		return (closing);
	}
	return (closing);
}

void		add_handled_token(char *value, enum e_tokens name, int priority,
	int splitter)
{
	t_handled_token *item;
	t_handled_token	*tmp;

	if (!(item = malloc(sizeof(*item))))
		exit_shell_code("malloc error", MALLOC_FAILURE);
	item->value = ft_strdup(value);
	item->name = name;
	item->priority = priority;
	item->closing = get_closing(value);
	item->splitter = splitter;
	item->next = NULL;
	if (g_shell->handled_token == NULL)
	{
		g_shell->handled_token = item;
		return ;
	}
	tmp = g_shell->handled_token;
	while (g_shell->handled_token->next)
		g_shell->handled_token = g_shell->handled_token->next;
	g_shell->handled_token->next = item;
	g_shell->handled_token = tmp;
}

void		set_handled_token(void)
{
	add_handled_token("${", DOLLARBRACE_TOKEN, 6, 0);
	add_handled_token(">>", DGREAT_TOKEN, 4, 1);
	add_handled_token("<<", DLESS_TOKEN, 4, 1);
	add_handled_token("||", OR_IF_TOKEN, 1, 1);
	add_handled_token("<>", LESSGREAT_TOKEN, 4, 1);
	add_handled_token("<&", LESSAND_TOKEN, 4, 1);
	add_handled_token(">&", GREATAND_TOKEN, 4, 1);
	add_handled_token("&>", ANDGREAT_TOKEN, 4, 1);
	add_handled_token("&&", AND_IF_TOKEN, 1, 1);
	add_handled_token("~", TILDE_TOKEN, 6, 0);
	add_handled_token("$", DOLLAR_TOKEN, 6, 0);
	add_handled_token("|", PIPE_TOKEN, 3, 1);
	add_handled_token("&", JOBCONTROL_TOKEN, 2, 1);
	add_handled_token(">", GREAT_TOKEN, 4, 1);
	add_handled_token("<", LESS_TOKEN, 4, 1);
	add_handled_token("}", RBRACE_TOKEN, 5, 0);
	add_handled_token(";", SEMICOLON_TOKEN, 0, 1);
	add_handled_token("=", ASSIGN_TOKEN, 6, 0);
	add_handled_token("!", HISTORY_TOKEN, 6, 0);
	add_handled_token("\"", DQUOTE, 11, 0);
	add_handled_token("'", QUOTE, 11, 1);
}
