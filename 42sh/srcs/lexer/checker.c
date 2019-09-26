/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 06:54:04 by bjovanov          #+#    #+#             */
/*   Updated: 2019/08/01 19:28:01 by bjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
** Verifie si le token actuel est une redirection
*/

int			is_redirect_token(enum e_tokens name)
{
	if (name == DGREAT_TOKEN || name == DLESS_TOKEN ||
		name == LESSAND_TOKEN || name == GREATAND_TOKEN ||
		name == ANDGREAT_TOKEN || name == GREAT_TOKEN || name == LESS_TOKEN)
		return (1);
	return (0);
}

/*
** Lance une nouvelle ligne dans le terminal pour terminer la commande
** et strjoin() la commande actuel avec ce qui est entre dans le terminal
*/

int			ft_restart(char **line, t_token **tokens, t_termcaps *termcaps,
			char *last_char)
{
	char *nline;
	char *tmp;

	nline = termcaps_main(termcaps, 2);
	if (g_shell->stop == 1)
	{
		delete_token_list(tokens);
		ft_strdel(&nline);
		return (0);
	}
	tmp = *line;
	if (ft_strequ("|", last_char))
		*line = ft_str3join(*line, " ", nline);
	else
		*line = ft_strjoin(*line, nline);
	ft_strdel(&tmp);
	ft_strdel(&nline);
	delete_token_list(tokens);
	close_command(line, termcaps);
	*tokens = lexer(line);
	if (!check_token_list(tokens, line, termcaps))
		return (0);
	return (1);
}

/*
** Verifie qu'on a bien un format comme suit:
** COMMAND_TOKEN + SPLITTER_TOKEN + COMMAND_TOKEN ...
** Prend en compte l'exception du job control qui peut
** se placer n'importe où
*/

int			alternate_cmd(t_token **tmp)
{
	int	cmd;

	cmd = 1;
	while (*tmp)
	{
		if ((*tmp)->name == JOBCONTROL_TOKEN && (*tmp)->next &&
			is_redirect_token((*tmp)->next->name))
		{
			*tmp = (*tmp)->next;
			continue ;
		}
		else if (cmd && (*tmp)->name == COMMAND_TOKEN)
			cmd = 0;
		else if (!cmd && (*tmp)->name != COMMAND_TOKEN)
			cmd = 1;
		else
			return (syntax_error((*tmp)->value));
		if ((*tmp)->next == NULL)
			break ;
		*tmp = (*tmp)->next;
	}
	return (1);
}

/*
** Fonction qui verifie la liste de tokens
** Verifie que le premier token est bien un COMMAND_TOKEN ou une redirection
** et rien d'autre sinon, erreur de syntaxe.
** Appelle alternate_cmd() pour verifier qu'on a bien le format suivant:
** COMMAND_TOKEN + SPLITTER_TOKEN + COMMAND_TOKEN ...
** Verifie egalement que le dernier token est bien un COMMAND_TOKEN.
** S'il s'agit d'un || ou d'un && ou d'un | non echappes, alors on
** appelle restart() pour creer une nouvelle ligne de termcaps afin de terminer
** la commande
*/

int			check_token_list(t_token **tokens, char **line, t_termcaps *term)
{
	t_token *t;

	t = *tokens;
	if ((is_redirect_token(t->name)) &&
		t->next && t->next->name == COMMAND_TOKEN)
		t = t->next;
	if (t->name != COMMAND_TOKEN)
		return (syntax_error(is_redirect_token(t->name) ? "\\n" : t->value));
	if (!alternate_cmd(&t))
		return (0);
	if (is_redirect_token(t->name))
		return (syntax_error("\\n"));
	if (t->name == OR_IF_TOKEN || t->name == AND_IF_TOKEN ||
		t->name == PIPE_TOKEN || count_backslashes(t->value,
			ft_strlen(t->value) - 1) % 2 != 0)
		if (!ft_restart(line, tokens, term, t->value))
			return (0);
	order_redirection(tokens);
	return (1);
}
