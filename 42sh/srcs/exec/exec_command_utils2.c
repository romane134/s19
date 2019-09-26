/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 21:49:07 by vjovanov          #+#    #+#             */
/*   Updated: 2019/07/17 17:39:30 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
** Fonction a nouveau un peu redondante utilise uniquement une fois.
** Utiliser plutot has_bad_subsitution.
*/

int			is_bad_substitution(char **cmd, int j, int i)
{
	char	*component;
	int		*quote;

	i = -1;
	component = NULL;
	quote = (int*)malloc(sizeof(int) * 2);
	ft_intset(quote, 2, 0);
	while (cmd[++i])
	{
		j = -1;
		while (cmd[i][++j])
		{
			if ((cmd[i][j] == '\'' || cmd[i][j] == '"')
					&& !is_escaped(cmd[i], j))
				recognize_quote(&quote, &(cmd[i][j]));
			if (ft_strnequ(&(cmd[i][j]), "${", 2) && !is_escaped(cmd[i], j)
					&& !(quote[0]))
			{
				component = get_varname(&(cmd[i][j]));
				print_error(component, "bad substitution");
				return (free_array_int(quote, free_array(component, 1)));
			}
		}
	}
	return (free_array_int(quote, 0));
}

/*
** Fonction qui extrait la variable responsable du bad substitution
** et ecrit l'erreur a l'ecran.
** Appele par la fonction has_bad_substitution
** retourne ensuite le code d'erreur 1
*/

static int	has_a_bad_substitution(char *cmd, int start)
{
	char *varname;

	varname = NULL;
	if (!(varname = ft_strsub(cmd, start, ft_strclen(&(cmd[start]), '}') + 1)))
		exit_shell_code("malloc error", MALLOC_FAILURE);
	print_error(varname, "bad substitution");
	return (free_array(varname, 1) && (g_shell->exit_status = 1) == 1);
}

/*
** Fonction utilise partout où on veut tester si une commande possede un
** "Bad Substitution".
** Un bad subsitution ne peut survenir que dans le cas d'une utilisation d'un
** expansion brace dollar (${}) et que son contenu n'est pas uniquement
** compose de caractere alphanumerique ou underscore.
*/

int			has_bad_substitution(char *cmd)
{
	int i;
	int check;
	int start;

	i = 0;
	check = 0;
	while (cmd[i])
	{
		if (check && ft_strclen(&(cmd[i]), '}') == 1 && cmd[i] == '?')
			return (0);
		if (check && !ft_isalnum(cmd[i]) && cmd[i] != '_')
			return (has_a_bad_substitution(cmd, start));
		if (ft_strnequ(&(cmd[i]), "${", 2) && !is_escaped(cmd, i))
		{
			start = i;
			i += 2;
			check = 1;
			continue ;
		}
		if (cmd[i] == '}')
			check = 0;
		i++;
	}
	return (0);
}

/*
** Duplique l'environnement
*/

char		**dup_env(char **environ)
{
	char	**new_environ;
	int		i;

	i = 0;
	while (environ[i])
		i++;
	new_environ = (char**)malloc(sizeof(char*) * (i + 1));
	new_environ[i] = NULL;
	i = 0;
	while (environ[i])
	{
		new_environ[i] = ft_strdup(environ[i]);
		i++;
	}
	return (new_environ);
}

/*
** Fonction appele dans le exec_command et qui a pour but de creer un
** environnement temporaire en se basant sur des infos recu
** Ex: HOME=/ cd
** Il faut creer un environnement temporaire dans lequel on modifie la
** variable HOME et qui ne sera utilise que le temps de la commande 'cd'
*/

void		set_temp_env(char **var, char ***tmp_env, char ***env)
{
	char	**split_var;
	int		i;

	i = 0;
	split_var = NULL;
	if (!(*tmp_env = dup_env(*env)))
		exit_shell_code("malloc error", MALLOC_FAILURE);
	while (var[i] && ft_strchr(var[i], '='))
	{
		if (!(split_var = ft_strsplit(var[i], '=')))
			exit_shell_code("malloc error", MALLOC_FAILURE);
		builtin_setenv(split_var, tmp_env);
		free_darray(split_var, 1);
		i++;
	}
}
