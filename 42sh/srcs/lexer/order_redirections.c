/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   order_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 10:21:45 by bjovanov          #+#    #+#             */
/*   Updated: 2019/08/01 19:33:18 by bjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
** Compte le nombre de mots en prenant en compte les variables, les tildes, les
** echappements et les inhibiteurs
*/

int					count_words_redirection(char *var, int *quote)
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

void				mansplitting(char **array, char **array2,
					char **space, int i)
{
	if (array2[1] == NULL)
		array2[1] = ft_strjoin("", array[i]);
	else
	{
		array2[1] = ft_strjoin_free(&(array2[1]), space, 0);
		array2[1] = ft_strjoin_free(&(array2[1]), &(array[i]), 2);
	}
	if (array2[1] == NULL)
		exit_shell_code("malloc error", MALLOC_FAILURE);
}

/*
** Split une chaine comme "a b c d e" en "a" et "b c d e"
*/

char				**split_io_file(char *value, char **space)
{
	char	**array;
	char	**array2;
	int		i;
	char	*tmp;

	i = 0;
	array2 = NULL;
	if (!(array = parse_cmd(value)) ||
		!(array2 = (char**)malloc(sizeof(char*) * 3)))
		exit_shell_code("malloc error", MALLOC_FAILURE);
	if (!(array2[0] = ft_strdup(array[0])))
		exit_shell_code("malloc error", MALLOC_FAILURE);
	array2[1] = NULL;
	array2[2] = NULL;
	tmp = NULL;
	while (array[++i])
	{
		mansplitting(array, array2, space, i);
	}
	free(array);
	return (array2);
}

/*
** Tant que les redirections ne sont pas ordonnees (c'est a dire qu'elles
** contiennent plus que UN nom de fichier), on boucle.
** On utilise io_split() pour obtenir 2 elements dans le cas où on la valeur
** est "a b c d e f g":
** on obtient "a" et "b c d e f g"
** et ce "b c d e f g", on le strjoin avec la valeur du token precedent
**
** Dans le cas où la commande est "> ls a b c", etant donne qu'on a pas de token
** precedent sur lequel mettre la valeur "a b c", on cree un nouveau token
** au debut de la liste avec la valeur "a b c"
*/

void				ordering(t_token **tokens, char ***array, char **tmpchar,
					char **space)
{
	t_token *last;
	t_token *tmp;

	tmp = *tokens;
	while ((last = redirection_not_ordered(*tokens)))
	{
		*array = split_io_file(last->value, space);
		ft_strdel(&(last->value));
		if (!(last->value = ft_strdup((*array)[0])))
			exit_shell_code("malloc error", MALLOC_FAILURE);
		ft_strdel(&((*array)[0]));
		*tmpchar = ft_strjoin_free(tmpchar, space, 0);
		if (!(*tmpchar = ft_strjoin_free(tmpchar, &((*array)[1]), 2)))
			exit_shell_code("malloc error", MALLOC_FAILURE);
		if (last->prev->prev)
		{
			if (!(last->prev->prev->value =
				ft_strjoin_free(&(last->prev->prev->value), tmpchar, 2)))
				exit_shell_code("malloc error", MALLOC_FAILURE);
		}
		else
			add_front_token(tokens, *tmpchar, COMMAND_TOKEN, 10);
		free(*array);
	}
	ft_strdel(tmpchar);
}

/*
** Permet d'ordonner les mauvaises redirections
** Une commande comme celle-ci:
** ls -l > a b c > d e f g
** n'est pas possible car il ne peut y avoir que UN nom de fichier donc on doit
** l'ordonner pour remettre les mots en trop a l'avant
** Ainsi, a la fin de l'order_redirection(), la commande doit ressembler a:
** ls -l b c e f g > a > d
**
** Donc on boucle sur chaque token, s'il s'agit d'un token de redirection, on
** compte le nombre de mots qu'il contient et s'il en contient plus que 1,
** on prend les mots en trop et on les met a la valeur du token precedent
** Et ainsi, on recommence jusqu'a ce que toutes les redirections soit bonnes.
**
** Dans l'exemple precedent, voici les differentes etapes:
** Situation de depart:
** ls -l > a b c > d e f g
**
** 1er tour de boucle:
** ls -l > a b c e f g > d
**
** 2eme tour de boucle:
** ls -l b c e f g > a > d
**
** Pas besoin de 3ieme tour de boucle car toutes les redirections sont bonnes
*/

void				order_redirection(t_token **tokens)
{
	char	**array;
	char	*tmpchar;
	char	*space;
	t_token	*tmp;

	space = ft_strdup(" ");
	if (space == NULL || !(tmpchar = ft_strnew(0)))
		exit_shell_code("malloc error", MALLOC_FAILURE);
	ordering(tokens, &array, &tmpchar, &space);
	tmp = *tokens;
	while (tmp)
	{
		if (tmp->prev && is_redirect_token(tmp->prev->name))
		{
			array = parse_cmd(tmp->value);
			clear_cmd(array);
			ft_strdel(&tmp->value);
			if (!(tmp->value = ft_strdup(array[0])))
				exit_shell_code("malloc error", MALLOC_FAILURE);
			delete_array(array);
		}
		tmp = tmp->next;
	}
	clear_token_list(tokens);
	ft_strdel(&space);
}
