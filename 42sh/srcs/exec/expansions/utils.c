/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 21:50:08 by vjovanov          #+#    #+#             */
/*   Updated: 2019/07/06 19:06:26 by bjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
** Verifie qu'une chaine de caractere est uniquement compose de caractere
** alphanumerique
*/

int		is_only_alphanum(char *cmd)
{
	int i;

	i = -1;
	if (cmd[0] == '\0' || cmd[0] == '}')
		return (0);
	while (cmd[++i])
	{
		if (cmd[i + 1] == '\0' && cmd[i] == '}')
			break ;
		if (!ft_isalnum(cmd[i]) && cmd[i] != '_')
			return (0);
	}
	return (1);
}

/*
** Fonction utilise la par la gestion de l'expansion dollar pour savoir
** si un nom de variable correspond a une variable interne
** Il va donc s'occuper de checker dans la table de hash g_shell->intern_hash
** pour savoir si il trouve quelque chose
**
** Si oui, il retourne 1,
** Si non, il retourne 0
*/

int		is_an_intern(char *varname, char **cmd)
{
	char	*replacement;
	char	*varname_clean;
	int		j;
	char	*tmp;

	replacement = NULL;
	tmp = NULL;
	j = 0;
	if ((*(varname + 1)) == '{')
		j = 1;
	if (!(varname_clean = ft_strsub(varname, j + 1,
		ft_strlen(varname + j + 1) - j)))
		exit_shell_code("malloc error", MALLOC_FAILURE);
	if ((replacement = find_hash(g_shell->intern_hash,
					varname_clean, INTERN_HASH_SIZE)) != NULL)
	{
		tmp = *cmd;
		if (!(*cmd = ft_streplace_first(*cmd, varname, replacement)))
			exit_shell_code("malloc error", MALLOC_FAILURE);
		ft_strdel(&tmp);
		return (free_array(varname_clean, 1) && free_array(replacement, 1));
	}
	return (free_array(varname_clean, 0) || free_array(replacement, 0));
}

/*
** Fonction utilise par la gestion de l'expansion dollar pour savoir si
** la variable envoye en parametre est egale a '?'.
** Si oui, il s'occupe de remplacer dans la chaine de caractere **cmd
** la variable $? ou ${?} par la valeur stocke dans g_shell->exit_status
*/

int		is_question_mark(char *varname, char **cmd)
{
	char	*replacement;
	int		j;
	char	*varname_clean;
	char	*tmp;

	replacement = NULL;
	tmp = NULL;
	j = 0;
	if ((*(varname + 1)) == '{')
		j = 1;
	if (!(varname_clean = ft_strsub(varname, j + 1,
		ft_strlen(varname + j + 1) - j)))
		exit_shell_code("malloc error", MALLOC_FAILURE);
	if (ft_strchr(varname_clean, '?') != NULL && ft_strlen(varname_clean) == 1)
	{
		if (!(replacement = ft_itoa(g_shell->exit_status)))
			exit_shell_code("malloc error", MALLOC_FAILURE);
		tmp = *cmd;
		if (!(*cmd = ft_streplace_first(*cmd, varname, replacement)))
			exit_shell_code("malloc error", MALLOC_FAILURE);
		ft_strdel(&tmp);
		return (free_array(varname_clean, 1) && free_array(replacement, 1));
	}
	return (free_array(varname_clean, 0) || free_array(replacement, 0));
}
