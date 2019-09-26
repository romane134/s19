/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 12:43:00 by bcedric           #+#    #+#             */
/*   Updated: 2019/08/01 17:38:21 by bjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
** Supprime une chaine de caractere et retourne la valeur definie
*/

int		free_array(char *array, int return_value)
{
	ft_strdel(&array);
	return (return_value);
}

/*
** Supprime un tableau a deux dimensions et retourne la valeur definie
*/

int		free_darray(char **array, int return_value)
{
	int i;

	i = 0;
	if (array == NULL)
		return (return_value);
	while (array[i])
	{
		ft_strdel(&(array[i]));
		i++;
	}
	free(array);
	array = NULL;
	return (return_value);
}

/*
** Supprime un tableau de int et retourne la valeur definie
*/

int		free_array_int(int *array, int return_value)
{
	free(array);
	return (return_value);
}

/*
** Supprime une chaine de caractere et exit le shell
*/

void	free_array_exit(char *array)
{
	ft_strdel(&array);
	exit_shell_code("malloc error", MALLOC_FAILURE);
}

/*
** Supprime un tableau a deux dimensions
*/

void	delete_array(char **array1)
{
	int i;

	i = 0;
	while (array1[i])
	{
		ft_strdel(&(array1[i]));
		i++;
	}
	free(array1);
	array1 = NULL;
}
