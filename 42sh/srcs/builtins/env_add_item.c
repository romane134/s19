/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_add_item.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 15:18:40 by bcedric           #+#    #+#             */
/*   Updated: 2019/07/02 22:34:04 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static int		key_exist_env(char **env, char *key)
{
	int		i;
	char	**arr;
	char	**arr_env;

	i = 0;
	arr = ft_strsplit(key, '=');
	while (env[i])
	{
		arr_env = ft_strsplit(env[i], '=');
		if (ft_strequ(arr[0], arr_env[0]))
		{
			delete_array(arr);
			delete_array(arr_env);
			return (i);
		}
		delete_array(arr_env);
		i++;
	}
	delete_array(arr);
	return (-1);
}

static int		update_env(char ***env, int index, char *cmd)
{
	ft_strdel(&((*env)[index]));
	if (!((*env)[index] = ft_strdup(cmd)))
		exit_shell_code("malloc error", MALLOC_FAILURE);
	return (1);
}

static int		add_env(char ***env, char *cmd)
{
	char	**copy;
	int		i;

	i = -1;
	if (!(copy = (char**)malloc(sizeof(char*) *
		(ft_array_length((void**)*env) + 2))))
		exit_shell_code("malloc error", MALLOC_FAILURE);
	while ((*env)[++i])
	{
		if (!(copy[i] = ft_strdup((*env)[i])))
			exit_shell_code("malloc error", MALLOC_FAILURE);
	}
	if (!(copy[i++] = ft_strdup(cmd)))
		exit_shell_code("malloc error", MALLOC_FAILURE);
	copy[i] = NULL;
	delete_array(*env);
	*env = copy;
	return (1);
}

int				setenv_tmp_env(char *cmd, char ***env, int *end)
{
	int	index;

	*end = 1;
	if (!is_valide_key(cmd))
		return (error_setenv_tmp(cmd));
	if ((index = key_exist_env(*env, cmd)) != -1)
		update_env(env, index, cmd);
	else
		add_env(env, cmd);
	return (1);
}
