/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 17:23:26 by bjovanov          #+#    #+#             */
/*   Updated: 2019/07/02 22:34:02 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		count_items(char **env, char **cmd)
{
	int		i;
	int		j;
	int		count;
	char	**item;

	i = -1;
	count = 0;
	item = NULL;
	while (env[++i])
	{
		if (!(item = ft_strsplit(env[i], '=')))
			exit_shell_code("malloc error", MALLOC_FAILURE);
		j = -1;
		while (cmd[++j])
		{
			if (ft_strequ(item[0], cmd[j]))
				count++;
		}
		delete_array(item);
	}
	return (ft_array_length((void**)env) - count);
}

int		deleted_item(char *item, char **cmd)
{
	int		i;
	char	**curr;

	i = -1;
	curr = NULL;
	if (!(curr = ft_strsplit(item, '=')))
		exit_shell_code("malloc error", MALLOC_FAILURE);
	while (cmd[++i])
	{
		del_hash(cmd[i], INTERN_HASH_SIZE, g_shell->intern_hash);
		if (ft_strequ(cmd[i], curr[0]))
		{
			delete_array(curr);
			return (1);
		}
	}
	delete_array(curr);
	return (0);
}

int		delete_env_item(char ***env, char **cmd, char ***copy)
{
	int i;
	int j;

	i = -1;
	j = 0;
	while ((*env)[++i])
	{
		if (!deleted_item((*env)[i], cmd))
			(*copy)[j++] = ft_strdup((*env)[i]);
	}
	(*copy)[j] = NULL;
	return (1);
}

int		builtin_unsetenv(char **cmd, char ***env)
{
	int		i;
	int		params;
	char	**copy;

	params = ft_array_length((void**)cmd);
	if (params == 0)
	{
		ft_putendl_fd("unsetenv: Too few arguments.", 2);
		return (1);
	}
	i = 0;
	if (!(copy = (char**)malloc(sizeof(char*) * (count_items(*env, cmd) + 1))))
		exit_shell_code("malloc error", MALLOC_FAILURE);
	delete_env_item(env, cmd, &copy);
	delete_array(*env);
	*env = copy;
	return (0);
}
