/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 19:54:36 by vjovanov          #+#    #+#             */
/*   Updated: 2019/07/06 19:00:08 by bjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
** Fonction qui s'occupede verifier si un backslash est un backslash 'escaper'
** ou escape
** Fonction un peu inutile et peu generique qui m'a peu servi mais
** malheureusement j'ai base un algo avec cette fonction donc trop complique
** de revenir en arriere
*/

int			is_escape_backslash(char *cmd, int i)
{
	int count_slash;

	count_slash = 0;
	if (i == 0)
		return (1);
	while (i >= 0)
	{
		if (cmd[i] == '\\')
			count_slash++;
		else
			break ;
		i--;
	}
	return (count_slash % 2);
}

/*
** Fonction qui s'occupe d'indiquer dans le tableau **quote
** si un quote ou un dquote est actif.
** S'occupe egalement de definir un quote ou dquote en actif ou inactif
** Fonctionne exactement comme l'historique, je sais pas pourquoi on
** a pas utilise l'historique mais bon a nouveau, pas moyen de supprimer
** car trop utilise dans des coeurs de fonction
*/

void		recognize_quote(int **quote, char *str)
{
	if (str[0] == '"')
	{
		if ((*quote)[1] == 1)
			(*quote)[1] = 0;
		else
		{
			if ((*quote)[0] == 0)
				(*quote)[1] = 1;
		}
	}
	else if (str[0] == '\'')
	{
		if ((*quote)[0] == 1)
			(*quote)[0] = 0;
		else
		{
			if ((*quote)[1] == 0)
				(*quote)[0] = 1;
		}
	}
}

/*
** Fonction utilise dans le parse_cmd pour splitter au bons endroit
** Si var[i] = '{', dans ce cas, il va avancer dans la chaine jusqu'a
** trouver un '}' et retourner le nombre d'index qu'il a avancer pour trouver
** le close_brace
*/

int			look_for_close_brace(char *var, int i)
{
	int			supp;

	supp = 0;
	while (var[i + supp])
	{
		if (var[i + supp] == '}' && !is_escaped(var, i + supp))
			return (supp);
		supp++;
	}
	return (supp);
}

/*
** Fonction ULTRA IMPORTANTE
** Il FAUT TOUJOURS definir ici les nouveaux builtins qu'on cree
** Fonction qui verifie si la commande envoye en parametre est un builtin
** Si oui, retourne 1
** Si non, retourne 0
*/

int			is_builtin(char *cmd)
{
	if (ft_strequ(cmd, "cd") || ft_strequ(cmd, "echo") ||
		ft_strequ(cmd, "env") || ft_strequ(cmd, "setenv") ||
		ft_strequ(cmd, "unsetenv") || ft_strequ(cmd, "exit") ||
		ft_strequ(cmd, "hash") || ft_strequ(cmd, "fc"))
		return (1);
	return (0);
}

/*
** INFOS:
**	Ne pas free la variable **split_var dans le cas où elle est
**	utilise dans la table de hash interne. Les adresses ne sont
**	pas copies
*/

/*
** Fonction qui s'occupe de stocker des variable interne
**
** Ex: a=b c=d ls -la
** 		Dans ce cas on stoke a=b et c=d dans la hash interne
**
** Premierement, verifie que la variable n'existe pas en variable
** d'environnement. Si la variable correspond a une cle dans
** l'environnement, dans ce cas, il va modifier la variable d'environnement
** Sinon, il va stocker dans la hash interne
*/

void		set_intern_var(char **var)
{
	char	**split_var;
	int		i;

	i = 0;
	split_var = NULL;
	while (var[i] && ft_strchr(var[i], '='))
	{
		if (!(split_var = ft_strsplit(var[i], '=')))
			exit_shell_code("malloc error", MALLOC_FAILURE);
		if (ft_getenv(split_var[0]) != NULL)
		{
			builtin_setenv(split_var, &(g_shell->env));
			free_darray(split_var, 1);
		}
		else
			add_data_hash(split_var[0], split_var[1],
						INTERN_HASH_SIZE, g_shell->intern_hash);
		i++;
	}
}
