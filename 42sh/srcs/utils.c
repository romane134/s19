/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:18:40 by bjovanov          #+#    #+#             */
/*   Updated: 2019/08/01 17:23:41 by bjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
** Quitte le shell avec le message approprie
*/

void	exit_shell(char *error)
{
	ft_putstr_fd("42sh: abort: ", 2);
	ft_putendl_fd(error, 2);
	exit(EXIT_FAILURE);
}

/*
** Utilise dans le lexeur
** Permet d'interrompre le lexing lorsqu'il y a une erreur de syntaxe
*/

int		syntax_error(char *token)
{
	ft_putstr_fd("42sh: syntax error near unexpected token `", 2);
	g_shell->exit_status = 1;
	ft_putstr_fd(token, 2);
	ft_putendl_fd("`", 2);
	return (0);
}

/*
** Affiche une erreur a l'ecran (sur la sortie d'erreur)
** Exemple: 42sh: cd: No such file or directory
** où "cd" est *component et "No such file or directory" est *error
*/

void	print_error(char *component, char *error)
{
	ft_putstr_fd("42sh: ", 2);
	ft_putstr_fd(component, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(error, 2);
}

/*
** Reset l'entree standard lorsqu'elle a ete prealablement redirige vers un
** autre file descriptor
*/

void	reset_stdin(void)
{
	dup2(g_shell->stdin_copy, 0);
	close(g_shell->stdin_copy);
}

/*
** /!\ Fonction depreciee /!\
** Utiliser plutôt is_escaped() situee dans le fichier expansion.c
**
** Compte le nombre de backslash avant un caractere pour determiner si le
** caractere en cours est echappe
*/

int		count_backslashes(char *line, int i)
{
	int backslashes;

	backslashes = 0;
	while (line[i] == '\\')
	{
		backslashes++;
		i--;
	}
	return (backslashes);
}
