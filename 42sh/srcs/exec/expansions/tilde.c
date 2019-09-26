/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 13:36:27 by vjovanov          #+#    #+#             */
/*   Updated: 2019/07/02 22:33:56 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
** Fonction qui recupere le mot apres le tilde jusqu'a tomber sur un espace
** ou un slash
*/

char	*get_user(char *cmd)
{
	int i;

	i = 0;
	while (cmd[++i])
	{
		if (ft_isspace(cmd[i]) || cmd[i] == '/')
			break ;
	}
	return (ft_strsub(cmd, 0, i));
}

/*
** Fonction qui s'occupe de gerer le remplacement d'un tilde suivi par un slash
** ou une lettre
**
** Premierement, si le tilde est suivi d'une lettre, il va recuperer le mot
** jusqu'a tomber sur un slash ou un espace grace a la fct get_user
**
** Ensuite, il va, grace a ce mot, creer un path "/users/{word recupere}",
** et ensuite, il va s'occuper de lier ce path avec le reste et remplacer
** le tilde
*/

void	tilde_with_slash(char **usr, char ***cmd, int *i)
{
	char *replacement;
	char *tmp;

	replacement = NULL;
	if (!(*usr = get_user(&((**cmd)[*i]))))
		exit_shell_code("malloc error", MALLOC_FAILURE);
	if (!(replacement = ft_strjoin("/Users/", (*usr) + 1)))
		exit_shell_code("malloc error", MALLOC_FAILURE);
	tmp = **cmd;
	if (!(**cmd = ft_streplace_first(**cmd, *usr, replacement)))
		exit_shell_code("malloc error", MALLOC_FAILURE);
	ft_strdel(&tmp);
	ft_strdel(usr);
	*i += ft_strlen(replacement);
	ft_strdel(&replacement);
}

/*
** Fonction qui s'occupe de gerer le remplacement d'un tilde suivi par un espace
**
** Premierement, il verifie si la variable d'environnement HOME existe.
** Si oui,il remplace le tilde par la valeur associe a la variable HOME
** Si non, il remplace le tilde par une chaine de caractere vide
*/

void	tilde_without_slash(char ***cmd, char **environ, int *i)
{
	char	*replacement;
	int		index;
	char	*tmp;

	replacement = NULL;
	if ((index = is_in_env("HOME", environ)) > 0)
	{
		if (!(replacement = ft_strdup(&(environ[index]
			[ft_strclen(environ[index], '=') + 1]))))
			exit_shell_code("malloc error", MALLOC_FAILURE);
	}
	else
		replacement = ft_strdup("");
	if (replacement == NULL)
		exit_shell_code("malloc error", MALLOC_FAILURE);
	tmp = **cmd;
	if (!(**cmd = ft_streplace_first(**cmd, "~", replacement)))
		exit_shell_code("malloc error", MALLOC_FAILURE);
	ft_strdel(&tmp);
	*i += ft_strlen(replacement);
	ft_strdel(&replacement);
}

/*
** Fonction qui s'occupe des tildes.
**
** Pour le coup, je me rappelle plus pourquoi, mais je l'ai gere un peu
** comme zsh au lieu de bash.
**
** La premiere condition assez verbeuse s'occupe juste de verifier si:
** 		- le tilde est bien le premier caractere d'un mot ou alors
**			n'est pas oblige d'etre le premier caractere d'un mot si le
**			caractere qui le precede est un '='
**		- le tilde est bien suivi d'un espace, d'une lettre, d'un slash
**			ou un '\0'
** Si la condition est remplie, dans ce cas, il verifie si le tilde est
** suivi d'un slash ou d'un espace afin de savoir comment remplacer
** le tilde
**
** La fonction whitout_slash est appele si le tilde est suivi d'un espace
** La fonction with_slash est appele si le tilde est suvi d'un slash ou lettre
*/

void	expansion_tilde(char **cmd, char **environ)
{
	int		i;
	char	*usr;

	i = -1;
	usr = NULL;
	while ((*cmd)[++i])
	{
		if ((*cmd)[i] == '~' && !is_escaped(*cmd, i)
			&& !(i > 0 && !ft_isspace((*cmd)[i - 1]) && !((*cmd)[i - 1] == '='))
				&& (ft_isalpha((*cmd)[i + 1]) || ((*cmd)[i + 1] == '/')
					|| ((*cmd)[i + 1] == '\0' || ft_isspace((*cmd)[i + 1]))))
		{
			if (ft_isspace((*cmd)[i + 1])
				|| (*cmd)[i + 1] == '\0' || (*cmd)[i + 1] == '/')
				tilde_without_slash(&cmd, environ, &i);
			else
				tilde_with_slash(&usr, &cmd, &i);
		}
	}
}
