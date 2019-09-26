/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 09:14:38 by vjovanov          #+#    #+#             */
/*   Updated: 2019/08/01 18:25:51 by bjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
** Retourne le nombre de caracteres qu'il y a avant celui qu'on cherche
*/

int				length_to_next(char *searched, char *line, int i)
{
	int length;

	length = 1;
	while (!ft_strnequ(&(line[i + length]), searched, ft_strlen(searched)) ||
		(ft_strnequ(&(line[i + length]), searched, ft_strlen(searched)) &&
		is_escaped(line, i)))
		length++;
	return (length + 1);
}

/*
** Lorsqu'on splitte les tokens, il arrive souvent que les tokens commencent
** ou terminent par des espaces, donc on strtrim() chaque token pour eviter
** le probleme et si certains token, via le strtrim() n'ont plus aucune valeur
** (donc il ne s'agissait que d'espace), on les suppriment de la liste de tokens
*/

void			clear_token_list(t_token **tokens)
{
	t_token *tmp;
	char	*nvalue;

	tmp = *tokens;
	while (tmp)
	{
		if (!(nvalue = ft_strtrim((char const*)tmp->value)))
			exit_shell_code("malloc error", MALLOC_FAILURE);
		ft_strdel(&(tmp->value));
		tmp->value = nvalue;
		if (tmp->value[0] == '\0')
			delete_token(&tmp, tokens);
		tmp = tmp->next;
	}
}

/*
** Verifie si la chaine de caracteres passee ne contient que des espaces
*/

int				is_only_space(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (!ft_isspace(line[i]))
			return (0);
		i++;
	}
	return (1);
}

/*
** S'occupe de splitter les mots ou les phrases en differents token
** Dans la boucle, si le caractere en cours est un caractere qui doit être
** ferme (", ', ${, ...) il definit la taille du token jusqu'au caractere qui
** le ferme.
** Si le caractere est un caractere qui split (|, ||, &&, ...), on appelle
** handle_redirect() pour qu'il ajuste la taille si le token qui split est une
** redirection et on cree les deux tokens. Le COMMAND_TOKEN dont on a defini la
** taille juste avant et le splitter token sur lequel on se trouve
*/

void			while_lexer(char **line, int *i, int *length, t_token **tokens)
{
	int				redirect;
	t_handled_token *current;

	current = NULL;
	while ((*line)[++(*i)])
	{
		if ((current = is_closing_token(*line, *i)) != NULL)
		{
			*length += length_to_next(current->closing, *line, *i) + 1;
			*i += length_to_next(current->closing, *line, *i);
			continue ;
		}
		if ((current = is_splitter_token(*line, *i)) != NULL)
		{
			redirect = handle_redirect(*line, i, length, current);
			add_token(tokens, ft_strsub(*line, *i - *length, *length),
				COMMAND_TOKEN, 5);
			add_token(tokens, ft_strsub(*line, *i, redirect), current->name,
				current->priority);
			*length = 0;
			*i += redirect - 1;
			continue ;
		}
		(*length)++;
	}
}

/*
** Fonction principale du lexeur
** Verifie s'il ne s'agit que d'espaces ou de tabulations et arrête
** si c'est le cas
** Sinon appelle la fonction while_lexer() (expliquee juste au dessus),
** cree le token final (oui, c'etait uniquement pour la norme),
** et clear la liste de tokens
*/

t_token			*lexer(char **line)
{
	t_token			*tokens;
	int				i;
	int				length;

	tokens = NULL;
	i = -1;
	length = 0;
	if (*line == NULL)
		return (NULL);
	if (is_only_space(*line))
		return (NULL);
	while_lexer(line, &i, &length, &tokens);
	if (length > 0)
		add_token(&tokens, ft_strsub(*line, i - length, length),
				COMMAND_TOKEN, 10);
	clear_token_list(&tokens);
	return (tokens);
}
