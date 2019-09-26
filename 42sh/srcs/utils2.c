/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 22:14:22 by vjovanov          #+#    #+#             */
/*   Updated: 2019/08/01 17:26:49 by bjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Quitte le shell avec le message d'erreur approprie et un code de retour
** approprie
*/

#include "sh42.h"

int		exit_shell_code(char *error, int return_code)
{
	ft_putstr_fd("42sh: abort: ", 2);
	ft_putendl_fd(error, 2);
	exit(return_code);
}

/*
** Affiche un message d'erreur a l'ecran (sur la sortie d'erreur)
** et retourne une valeur definie
** Exemple: 42sh: cd: No such file or directory (et retourne 0)
** Où cd est *component, "No such file or directory" est *error et 0 est
** value_return
*/

int		print_error_return(char *component, char *error, int value_return)
{
	ft_putstr_fd("42sh: ", 2);
	ft_putstr_fd(component, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(error, 2);
	return (value_return);
}
