/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 13:36:22 by vjovanov          #+#    #+#             */
/*   Updated: 2019/08/01 23:22:02 by sstinglh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
** Fonctionne qui va chercher dans un double tableau de chaine de caractere
** une chaine de caractere en particulier et retourne l'index de la chaine
** de caractere dans laquelle il a trouve une correspondante
**
** ex: char **a = [
**				   "Hello les gens",
**				   "Salut la famille",
**				   "Wesh gros"
**				  ]
** int a = find_in_array(a, "famille")
** a = 1
*/

int		find_in_array(char **array, char *to_find)
{
	int		index;
	char	*is_in;

	index = 0;
	while (array[index])
	{
		if ((is_in = ft_strnstr(array[index], to_find,
			ft_strlen(to_find))) != NULL)
			return (index);
		index++;
	}
	return (-1);
}

/*
** Fonction qui permet de savoir si le caractere designe par i
** est escaped.
** char *command = la commande ou la chaine de caractere
** int i = l'index dans la chaine command du caractere dont on veut savoir
** 			si il est escaped
*/

int		is_escaped(char *command, int i)
{
	int count_slash;

	count_slash = 0;
	if (i == 0)
		return (0);
	i--;
	while (i >= 0)
	{
		if (command[i] == '\\')
			count_slash++;
		else
			break ;
		i--;
	}
	return (count_slash % 2);
}

/*
** Fonction utilise par l'expansion dollar pour extraire un nom de variable
** d'une chaine de caractere
** fonction non generique.
*/

char	*get_varname(char *cmd)
{
	int i;
	int size;

	i = 0;
	size = 0;
	if (cmd[i + 1] == '{')
	{
		i++;
		while (cmd[++i] != '}')
			size++;
		return (ft_strsub(cmd, 0, size + 3));
	}
	if (cmd[i + 1] == '?')
		return (ft_strsub(cmd, 0, 2));
	while (ft_isalnum(cmd[++i]) || cmd[i] == '_')
		size++;
	return (ft_strsub(cmd, i - size - 1, size + 1));
}

/*
** Fonction qui permet de verifier si une variable nomme grace a 'varname'
** existe dans l'environnement envoye en parametre
** char *varname = le nom de la variable
** char **environ = l'environnement
*/

int		is_in_env(char *varname, char **environ)
{
	char	*final_var;
	int		index;
	char	*tmp;

	if (!(tmp = ft_strdup(varname)))
		exit_shell_code("malloc error", MALLOC_FAILURE);
	if (varname[0] == '{')
	{
		ft_strdel(&tmp);
		if (!(tmp = ft_strsub(varname, 1, ft_strlen(varname) - 2)))
			exit_shell_code("malloc error", MALLOC_FAILURE);
	}
	if ((final_var = ft_strjoin(tmp, "=")) == NULL)
		exit_shell_code("malloc error", MALLOC_FAILURE);
	ft_strdel(&tmp);
	index = find_in_array(environ, final_var);
	return (free_array(final_var, index));
}

/*
** Fonction qui dispatch la gestion des expansions
*/

int		expansions_handle(char **command, char **environ)
{
	expansion_dollar(command, environ);
	expansion_tilde(command, environ);
	return (1);
}
