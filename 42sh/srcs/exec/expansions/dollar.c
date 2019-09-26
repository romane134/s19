/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 11:52:30 by vjovanov          #+#    #+#             */
/*   Updated: 2019/07/06 19:05:58 by bjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
** Cette fonction est appele a chaque fois juste avant qu'une commande soit
** execute, donc en l'occurence dans exec_command_core.c
** Je comprends pas trop le principe de ce truc mais bon, il faut le faire.
** Ex: > ls -la Makefile
**     > echo $_
**     > Makefile
**
** Ex2: > ls -la
**      > echo $_
**      > -la
**
** En gros, le underscore stocke a chaque fois le dernier mot de la derniere
** commande execute
*/

int		set_underscore_var(char **cmd, char ***env)
{
	char	**options;
	char	*last_word;
	int		index;

	index = 0;
	while (cmd[index + 1] != NULL)
		index++;
	if (!(options = (char**)malloc(sizeof(char*) * 3)))
		exit_shell_code("malloc error", MALLOC_FAILURE);
	if (!(last_word = ft_strdup(cmd[index])))
		exit_shell("mallor error");
	options[0] = ft_strdup("_");
	options[1] = last_word;
	options[2] = NULL;
	builtin_setenv(options, env);
	return (free_darray(options, 1));
}

/*
** Une simple fonction qui remplace une variable par sa valeur correspondante
** recupere dans l'environnement.
** C'est une fonction qui est la pour passer la norminette, elle est pas
** du tout generique.
*/

int		replace_var(char **environ, int j, char **cmd, char *varname)
{
	char *replacement;
	char *tmp;

	if (!(replacement = ft_strdup(&(environ[j]
		[ft_strclen(environ[j], '=') + 1]))))
		exit_shell_code("malloc error", MALLOC_FAILURE);
	tmp = *cmd;
	if (!(*cmd = ft_streplace_first(*cmd, varname, replacement)))
		exit_shell_code("malloc error", MALLOC_FAILURE);
	ft_strdel(&tmp);
	ft_strdel(&replacement);
	return (ft_strlen(varname));
}

/*
** Cette fonction s'occupe de faire tous les checks pour savoir
** par quoi remplacer le nom de variable
** D'abord, il appelle la fonction get_varname qui extrait le nom de la variable
** ATTENTION: Il retourne pas le nom de la variable tel quel. C'est un peu
** 				une fonction spaghetti. Si par exemple, la variable = ${HOME}
**				il retourne quelque chose genre "{HOME". je m'occupe apres
**				de travailler dessus comme il faut.
**
** D'abord, grace au nom de la variable, je vais verifier dans l'environnement
** si ce nom de variable correspond a une cle.
** Si oui, je remplace le nom de variable par la valeur correspondante a la cle,
** et j'arrete la fonction pour continuer a verifier dans chaine de caractere
** si il n'y a pas d'autres dollar a remplacer
** Si non, je fais les tests suivant:
**
** je fais appel a is_question_mark pour savoir si c'est un $?.
** Si oui, la fonction is_question_mark dans le fichier expansions/utils.c
**  s'occupe de remplacer la variable par ce qu'il faut.
** Si non, je continue mes tests.
**
** Si ce n'est pas un question mark, alors je verifie si c'est un nom de
** variable qui correspond a une variable interne.
** Si oui, la fonction is_an_intern dans le fichier expansions/utils.c s'occupe
** de faire le remplacement par ce qu'il faut.
** si non, je continue mes tests.
**
** si ce n'est pas non plus une variable interne, dans ce cas, je verifie bien
** que le nom de la variable ne contient que du contenu alphanum.
** en realite, ce test sert surtout a savoir si il y a un "bad subsitution",
** car la fonction get_varname au debut s'occupe de verifier ca a ma place.
** Cependant, dans le cas d'un ${HELLO_}, get_varname me retourne HELLO_,
** donc, si il n'y a bien que du contenu alphanum, je remplace le nom de la
** variable par une chaine vide.
** Sinon, je ne la modifie pas et plus tard dans l'executeur, l'executeur
** va verifier si il ne reste pas de $, si il en reste un et qu'il n'est
** pas echappe, alors c'est qu'il y a eu un bad subsitution
*/

void	dollar(char **cmd, char **environ, int *i)
{
	char	*varname;
	int		j;
	char	*tmp;

	if ((varname = get_varname(&((*cmd)[*i]))) == NULL)
		exit_shell_code("malloc error", MALLOC_FAILURE);
	if (ft_strlen(varname + 1) >= 1
		&& ((j = is_in_env(varname + 1, environ)) != -1))
		*i += replace_var(environ, j, cmd, varname);
	else
	{
		if ((j = 1) == 1 && (*(varname + 1)) == '{')
			j = 2;
		if (!is_question_mark(varname, cmd))
			if (!is_an_intern(varname, cmd))
				if (is_only_alphanum(varname + j))
				{
					tmp = *cmd;
					if (!(*cmd = ft_streplace_first(*cmd, varname, "")))
						exit_shell_code("malloc error", MALLOC_FAILURE);
					ft_strdel(&tmp);
					*i -= ft_strlen(varname);
				}
	}
	free_array(varname, 0);
}

/*
** Gere les expansions dollars, la fonction est appelle a chaque
** debut d'execution de command_token
** Les fonctions d'historique qu'on peut voir ici me permettent de stocker
** le fait que je sois tombe sur un quote ou dquote car les quotes
** echappent absolument tout. ex: echo '$HOME' => $HOME
** contrairement aux dquotes qui eux n'echappent pas tout
** ex: echo '$HOME' => /Users/vjovanov
**
** donc j'ai besoin de cette historique pour savoir quand remplacer
** ou non le nom de la variable par sa valeur correspondante dans l'env.
*/

void	expansion_dollar(char **cmd, char **environ)
{
	t_history	*history;
	int			i;

	history = NULL;
	i = -1;
	while ((*cmd)[++i])
	{
		if (((*cmd)[i] == '"' || (*cmd)[i] == '\'') && !is_escaped(*cmd, i))
		{
			if (ft_strnequ(get_last_history_closing(history), &((*cmd)[i]), 1))
			{
				remove_last_history(&history);
				continue ;
			}
			if (get_last_history_closing(history) == NULL)
				add_history(&history, (*cmd)[i] == '"' ? "\"" : "'",
					(*cmd)[i] == '"' ? "\"" : "'");
		}
		if ((*cmd)[i] == '$' && !is_escaped(*cmd, i)
			&& !ft_strequ(get_last_history_opening(history), "'"))
			dollar(cmd, environ, &i);
	}
}
