/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 16:43:51 by bjovanov          #+#    #+#             */
/*   Updated: 2019/07/02 22:34:03 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		key_exists_in_env(char **env, char *key)
{
	int		i;
	char	**item;

	i = 0;
	item = NULL;
	while (env[i])
	{
		if (!(item = ft_strsplit(env[i], '=')))
			exit_shell_code("malloc error", MALLOC_FAILURE);
		if (ft_strequ(key, item[0]))
		{
			delete_array(item);
			return (i);
		}
		delete_array(item);
		i++;
	}
	return (-1);
}

int		is_valid_key(char *key)
{
	int i;

	i = 1;
	if (!ft_isalpha(key[0]) && key[0] != '_')
	{
		ft_putendl_fd("setenv: Variable must begin with a letter\n", 2);
		return (0);
	}
	while (key[i])
	{
		if (!ft_isalnum(key[i]))
		{
			ft_putendl_fd("setenv: Variable name must contains alphanumerics"
				" characters\n", 2);
			return (0);
		}
		i++;
	}
	return (1);
}

int		update_env_item(char ***env, int index, char **cmd)
{
	ft_strdel(&((*env)[index]));
	if (!((*env)[index] = ft_str3join(cmd[0], "=",
		cmd[1] == NULL ? "" : cmd[1])))
		exit_shell_code("malloc error", MALLOC_FAILURE);
	return (0);
}

int		add_env_item(char ***env, char **cmd)
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
	if (!(copy[i++] = ft_str3join(cmd[0], "=", cmd[1] == NULL ? "" : cmd[1])))
		exit_shell_code("malloc error", MALLOC_FAILURE);
	copy[i] = NULL;
	delete_array(*env);
	*env = copy;
	return (0);
}

int		builtin_setenv(char **cmd, char ***env)
{
	int	index;
	int options;

	options = ft_array_length((void**)cmd);
	if (options == 0)
		return (print_env(*env));
	if (options > 2)
	{
		ft_putendl_fd("setenv: Too many arguments.", 2);
		return (1);
	}
	if (!is_valid_key(cmd[0]))
		return (1);
	if ((index = key_exists_in_env(*env, cmd[0])) != -1)
		return (update_env_item(env, index, cmd));
	else
		return (add_env_item(env, cmd));
	return (0);
}
