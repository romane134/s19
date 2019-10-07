/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocompletion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smondesi <smondesi@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 16:22:56 by smondesi          #+#    #+#             */
/*   Updated: 2019/08/29 17:24:55 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

// void		ft_term_up(t_filename *fname, t_termcaps *termcaps)
// {
// 	while (fname)
// 	{
// 		tputs(tgoto(termcaps->goup, 0, 0), 1, (void *)ft_putchar);
// 		fname = fname->next;
// 	}
// 	tputs(tgoto(termcaps->goup, 0, 0), 1, (void *)ft_putchar);
// }

int debug_1()
{
	return (open("/Users/rlucas-d/Documents/42sh/debug_1", O_RDWR | O_CREAT | O_APPEND, 0755));
}
char	*autocomplete_main(char *cmd, int context)
{
	if (context == 1)
		return (autocompletion_dynamique(cmd));
	else if (context == 2)
		return (autocompletion_var_home(cmd));
	else if (context == 3)
		return (autocomplete_command(cmd));
	else
		return (autocomplete_path(cmd));
}

char	*ft_what_word(char *cmd, t_termcaps *t)
{
	char *word;

	t->auto_end = t->pos;
	t->auto_start = t->pos;
	if (cmd[t->auto_end] == ' ' || (t->pos == t->cmd_len && t->pos != 0))
	{
		t->auto_end--;
		t->auto_start--;
	}
	while (cmd[t->auto_end] && cmd[t->auto_end] != ' '
			&& t->auto_end < t->cmd_len)
		t->auto_end++;
	while (cmd[t->auto_start] && cmd[t->auto_start] != ' ' && t->auto_start > 0)
		t->auto_start--;
	if (cmd[t->auto_start] == ' ' && t->auto_end != t->auto_start)
	{
		t->auto_start++;
	}

	word = ft_strsub(cmd, t->auto_start, t->auto_end - t->auto_start);
	dprintf(debug_1(), "WORD:%s|\n", word);
	return (word);
}

char	*ft_put_back_word(char *cmd, t_termcaps *t, char **word)
{
	char *tmp;
	char *tmpo;

	tmp = ft_strsub(cmd, 0, t->auto_start);
	tmp = ft_strjoin_free(&tmp, word, 2);
	tmpo = ft_strsub(cmd, t->auto_end, ft_strlen(cmd) - t->auto_end);
	tmp = ft_strjoin_free(&tmp, &tmpo, 2);
	return (tmp);
}

int		ft_context(char *cmd, t_termcaps *t)
{
	int i;

	i = t->pos;
	if (cmd[i] == ' ')
		i--;
	while (i >= 0 && cmd[i] != ' ')
		i--;
// ft_printf("don4t go --> %c|%d\n", cmd[i + 1], i);
	if (cmd[i + 1] == '$')
		return (1); //var
	else if (cmd[i + 1] == '~' && (cmd[i + 2] == '/' ||
				cmd[i + 2] == ' ' || i + 2 == t->cmd_len))//add if follow by / or ''
		return (2); //HOME
	while (cmd[i] == ' ')
		i--;
// ft_printf("don4t go --> %c|%d\n", cmd[i], i);
	if (!ft_isalnum(cmd[i]) || i == -1)//mettre que les separatur
		return (3); //commande
	else
		return (4); //path
}

char	*autocomplete(char *cmd, t_termcaps *termcaps)
{
	char	*word;
	char	*tmp;
	int		context;

	word = ft_what_word(cmd, termcaps);
	context = ft_context(cmd, termcaps);
	// printf("==%d==\n", context);
	tmp = autocomplete_main(word, context);
	ft_strdel(&word);
	// printf("==%d==\n", context);
	cmd = ft_put_back_word(cmd, termcaps, &tmp);
	return (cmd);
}
