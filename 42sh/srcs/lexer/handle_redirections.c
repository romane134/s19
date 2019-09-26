/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 15:30:06 by bjovanov          #+#    #+#             */
/*   Updated: 2019/08/01 19:34:07 by bjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
** Verifie pour une redirection que le chiffre passe ou avant est bien un
** file descriptor du terminal (0, 1, 2) car on ne gere que ceux-la
*/

int					is_terminal_fd(char *str, int index)
{
	int i;

	i = index;
	while (index > 0 && !ft_isspace(str[index - 1]))
		index--;
	if (i - index != 0)
		return (0);
	if (str[index] == '0' || str[index] == '1' || str[index] == '2')
		return (1);
	return (0);
}

void				handle_terminal_fd(char *line, int *before, int *i,
					int *length)
{
	if (*before >= 0 && is_terminal_fd(line, *before))
	{
		(*length)--;
		(*i)--;
		(*before)--;
	}
	if (*before >= 0 && is_terminal_fd(line, *before + 1) &&
		!ft_isspace(line[*before]))
	{
		(*length)++;
		(*i)++;
		(*before)++;
	}
}

/*
** Modifie la length et *i par rapport aux redirections, le lexeur
** ne pouvant pas gerer directement le cas de chiffres avant et apres
** les redirections
**
** Ainsi, si on a cette commande: "ls 2>a", le lexeur va par defaut
** considerer ces trois token: "ls 2", ">", "a".
** Donc on va jouer avec la length pour qu'il considere plutôt ces
** trois token : "ls", "2>", "a"
*/

size_t				handle_redirect(char *line, int *i, int *length,
				t_handled_token *current)
{
	int before;
	int after;

	after = *i + (ft_strlen(current->value) > 1 ? 1 : 0);
	before = *i - 1;
	if (!ft_strnequ(&(line[*i]), "<", 1) && !ft_strnequ(&(line[*i]), ">", 1) &&
		!ft_strnequ(&(line[*i]), ">>", 2) && !ft_strnequ(&(line[*i]), "<<", 2)
		&& !ft_strnequ(&(line[*i]), "<&", 2) &&
		!ft_strnequ(&(line[*i]), ">&", 2) && !ft_strnequ(&(line[*i]), "&>", 2))
		return (ft_strlen(current->value));
	if (!ft_strnequ(&(line[*i]), "&>", 2))
	{
		handle_terminal_fd(line, &before, i, length);
	}
	if (is_token(&(line[before])) || ft_isspace(line[before]))
	{
		*length -= (*i - (before + 1));
		*i = before + 1;
	}
	return (after - before);
}

/*
** Verifie si une redirection n'est pas bien formattee, donc qu'elle a plus
** d'un mot et retourne la derniere redirection mal formattee trouvee
*/

t_token				*redirection_not_ordered(t_token *tokens)
{
	t_token	*tmp;
	t_token	*last;
	int		*quote;

	quote = malloc(sizeof(int) * 2);
	ft_intset(quote, 2, 0);
	tmp = tokens;
	last = NULL;
	while (tmp)
	{
		if (tmp->name == COMMAND_TOKEN && tmp->prev &&
			is_redirect_token(tmp->prev->name) &&
			count_words_redirection(tmp->value, quote) > 1)
			last = tmp;
		tmp = tmp->next;
	}
	free_array_int(quote, 1);
	return (last);
}
