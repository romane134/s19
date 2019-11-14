/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocompletion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smondesi <smondesi@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 16:22:56 by smondesi          #+#    #+#             */
/*   Updated: 2019/10/08 14:29:15 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char			*autocomplete_main(char *cmd, int context)
{
	int		i;
	char	*tmp;

	i = 0;
	if (context == 1)
		return (autocompletion_dynamique(cmd));
	else if (context == 2)
		return (autocompletion_var_home(cmd));
	else if (context == 3)
	{
		tmp = autocomplete_command(cmd, &i);
		if (i != 1)
			return (autocomplete_path(cmd));
		return (tmp);
	}
	else
		return (autocomplete_path(cmd));
}

void			ft_what_word(char *cmd, t_termcaps *t, char **word)
{
	char *tmp;

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
	tmp = ft_strsub(cmd, t->auto_start, t->auto_end - t->auto_start);
	(*word) = ft_strdup(tmp);
	ft_strdel(&tmp);
}

char			*ft_put_back_word(char *cmd, t_termcaps *t, char **word)
{
	char *tmp;
	char *tmpo;

	tmp = ft_strsub(cmd, 0, t->auto_start);
	tmp = ft_strjoin_free(&tmp, word, 2);
	tmpo = ft_strsub(cmd, t->auto_end, ft_strlen(cmd) - t->auto_end);
	tmp = ft_strjoin_free(&tmp, &tmpo, 2);
	return (tmp);
}

static int		ft_context(char *cmd)
{
	int i;
	int j;

	i = ft_strlen(cmd);
	if (cmd[i] && (cmd[i] == ' ' && (i >= 1 && (cmd[i] == '\0'))))
		i--;
	while (cmd[i] && ((i >= 0 && cmd[i] != ' ')))
		i--;
	i--;
	j = i;
	if (ft_strchr(cmd, '$') != NULL)
		while (j >= 0 && (cmd[j] != ' '))
		{
			if (cmd[j] == '$' && cmd[j + 1] != '{')
				return (1);
			j--;
		}
	else if (cmd && ft_strnequ(cmd + i - 1, "~/", 2) != 0)
		return (2);
	if ((isprintable(cmd) == 1 && cmd[i] != ' ') || is_only_space(cmd))
		return (3);
	return (4);
}

char			*autocomplete(char *cmd, t_termcaps *termcaps)
{
	char	*word;
	char	*tmp;
	int		context;

	ft_what_word(cmd, termcaps, &word);
	context = ft_context(cmd);
	tmp = autocomplete_main(word, context);
	ft_strdel(&word);
	cmd = ft_put_back_word(cmd, termcaps, &tmp);
	return (cmd);
}
