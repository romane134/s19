/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:09:28 by bjovanov          #+#    #+#             */
/*   Updated: 2019/07/02 22:34:07 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		len_env(char **env)
{
	int count;

	count = 0;
	while (env[count])
		count++;
	return (count);
}

void	set_environment(char **env)
{
	int i;

	g_shell->env = NULL;
	i = -1;
	if (!(g_shell->env = (char**)malloc(sizeof(char*) * (len_env(env) + 1))))
		exit_shell_code("malloc error", MALLOC_FAILURE);
	while (env[++i])
	{
		if (!(g_shell->env[i] = ft_strdup(env[i])))
			exit_shell_code("malloc error", MALLOC_FAILURE);
	}
	g_shell->env[i] = 0;
}

char	*ft_getenv(char *name)
{
	int		i;
	char	**item;
	int		keylen;

	i = -1;
	item = NULL;
	while (g_shell->env[++i])
	{
		if (!(item = ft_strsplit(g_shell->env[i], '=')))
			exit_shell_code("malloc error", MALLOC_FAILURE);
		if (ft_strequ(item[0], name))
		{
			keylen = ft_strlen(item[0]);
			delete_array(item);
			return (&(g_shell->env[i][keylen + 1]));
		}
		delete_array(item);
	}
	return (NULL);
}

char	*ft_getenv_choice(char *name, char **env)
{
	int		i;
	char	**item;
	int		keylen;

	i = -1;
	item = NULL;
	while (env[++i])
	{
		if (!(item = ft_strsplit(env[i], '=')))
			exit_shell_code("malloc error", MALLOC_FAILURE);
		if (ft_strequ(item[0], name))
		{
			keylen = ft_strlen(item[0]);
			delete_array(item);
			return (&(env[i][keylen + 1]));
		}
		delete_array(item);
	}
	return (NULL);
}
