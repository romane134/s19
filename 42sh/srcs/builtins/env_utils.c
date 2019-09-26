/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 15:15:44 by bcedric           #+#    #+#             */
/*   Updated: 2019/07/02 22:34:03 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int			is_variable_env(char *cmd, char c)
{
	int	i;

	i = -1;
	while (cmd[++i])
	{
		if (cmd[i] == c)
			return (1);
	}
	return (0);
}

int			is_valide_key(char *key)
{
	if (key[0] == '=')
		return (0);
	return (1);
}

char		**strdup_array(char **env, int j)
{
	char	**copy;
	int		i;

	if (j == 1)
	{
		if (!(copy = (char**)malloc(sizeof(char*) *
			ft_array_length((void**)env) + 1)))
			exit_shell_code("malloc error", MALLOC_FAILURE);
		i = -1;
		while (env[++i])
		{
			if (!(copy[i] = ft_strdup(env[i])))
				exit_shell_code("malloc error", MALLOC_FAILURE);
		}
		copy[i] = NULL;
	}
	else
	{
		if (!(copy = (char**)malloc(sizeof(char*) * 1)))
			exit_shell_code("malloc error", MALLOC_FAILURE);
		copy[0] = NULL;
	}
	return (copy);
}

int			find_index(char **cmd, int i)
{
	int	j;
	int	end;

	j = i - 1;
	while (cmd[++j])
	{
		end = 0;
		if (is_variable_env(cmd[j], '='))
			end = 1;
		if (end == 0)
			break ;
	}
	return (j);
}

char		*find_path(char *cmd)
{
	char	*path;

	if (!ft_strchr(cmd, '/'))
	{
		if (!(path = find_hash(g_hash_table, cmd, HASHTABLE_SIZE)))
			return (NULL);
		else
			path = ft_strdup(path);
	}
	else if (cmd[0] == '/')
		path = ft_strdup(cmd);
	else
		path = ft_str3join(getcwd(NULL, 0), "/", cmd);
	if (path == NULL)
		exit_shell_code("malloc error", MALLOC_FAILURE);
	return (path);
}
