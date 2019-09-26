/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command_splitter.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 20:08:47 by vjovanov          #+#    #+#             */
/*   Updated: 2019/07/16 10:09:28 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static int		count_words(char *var, int *quote)
{
	int i;
	int words;

	i = -1;
	words = 0;
	while (var[++i])
		if (!ft_isspace(var[i]))
		{
			if ((var[i] == '"' || var[i] == '\'') &&
				!(i > 0 && var[i - 1] == '\\' && is_escaped(var, i)))
				recognize_quote(&quote, &(var[i]));
			else if ((!quote[0] && !quote[1]) &&
			ft_strnequ(&(var[i]), "${", 2) && !is_escaped(var, i))
				i += look_for_close_brace(var, i);
		}
		else if (ft_isspace(var[i]) && (!quote[0] && !quote[1]))
		{
			if (var[i - 1] == '\\' && is_escape_backslash(var, i - 1))
				continue ;
			if (i > 0 && !ft_isspace(var[i - 1]))
				words++;
		}
	if (i > 0 && !ft_isspace(var[i - 1]))
		words++;
	return (words);
}

/*
** sew[0] : start
** sew[1] : end
** sew[2] : words
*/

int				sub_word_extension(char *var, int number, int **quote, int *sew)
{
	if (!ft_isspace(var[sew[1]]))
	{
		if ((var[sew[1]] == '"' || var[sew[1]] == '\'') &&
			!(sew[1] > 0 && var[sew[1] - 1] == '\\'
				&& is_escape_backslash(var, sew[1] - 1)))
			recognize_quote(&(*quote), &(var[sew[1]]));
		else if ((!(*quote)[0] && !(*quote)[1]) &&
			ft_strnequ(&(var[sew[1]]), "${", 2) && !is_escaped(var, sew[1]))
			return (sew[1] += look_for_close_brace(var, sew[1]));
	}
	else if (ft_isspace(var[sew[1]]) && (!(*quote)[0] && !(*quote)[1]))
	{
		if (var[sew[1] - 1] == '\\' && is_escape_backslash(var, sew[1] - 1))
			return (1);
		if (sew[1] > 0 && !ft_isspace(var[sew[1] - 1]))
			sew[2]++;
		if (number == sew[2])
			return (0);
		else if (number != sew[2])
			sew[0] = sew[1] + 1;
	}
	return (1);
}

char			*sub_word(char *var, int number, int *quote)
{
	int		sew[3];

	sew[0] = 0;
	sew[1] = -1;
	sew[2] = -1;
	while (var[++sew[1]])
	{
		if (sub_word_extension(var, number, &quote, sew) > 0)
			continue ;
		else
			break ;
	}
	if (sew[1] > 0 && !ft_isspace(var[sew[1] - 1]))
		sew[1]++;
	return (ft_strsub(var, sew[0], sew[1] - sew[0] - 1));
}

/*
** S'occupe de parser la commande, en gros, c'est un ft_strsplit pousse
** Il s'occupe de la gestion des quotes, dquotes et backslash.
**
** Aucune des fonction ici n'est generique et peut etre utilise en dehors
** du contexte de la fonction parse_cmd
*/

char			**parse_cmd(char *var)
{
	char	**array;
	int		words;
	int		i;
	char	*tmp;
	int		*quote;

	i = -1;
	if (!(quote = (int*)malloc(sizeof(int) * 2)))
		exit_shell_code("malloc error", MALLOC_FAILURE);
	ft_intset(quote, 2, 0);
	if (!(tmp = ft_strtrim(var)))
		exit_shell_code("malloc error", MALLOC_FAILURE);
	words = count_words(tmp, quote);
	array = NULL;
	ft_intset(quote, 2, 0);
	if (!(array = (char**)malloc(sizeof(char*) * (words + 1))))
		exit_shell_code("malloc error", MALLOC_FAILURE);
	array[words] = NULL;
	while (++i < words)
		if (!(array[i] = sub_word(tmp, i, quote)))
			exit_shell_code("malloc error", MALLOC_FAILURE);
	ft_strdel(&tmp);
	free_array_int(quote, 1);
	return (array);
}
