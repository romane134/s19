/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_link.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 18:54:23 by smondesi          #+#    #+#             */
/*   Updated: 2019/07/02 22:34:05 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int			construct_full_path(char *path, char ***env)
{
	char	cwd[PATH_MAX + 1];

	getcwd(cwd, PATH_MAX);
	if (!chdir(path))
	{
		getcwd(cwd, PATH_MAX + 1);
		ft_strdel(&(g_shell->pwd->oldpwd));
		g_shell->pwd->oldpwd = g_shell->pwd->pwd;
		if (!(g_shell->pwd->pwd = ft_strdup(cwd)))
			exit_shell_code("malloc error", MALLOC_FAILURE);
		call_set_env(env);
	}
	return (0);
}

void		prev_path(char **cur)
{
	int		i;
	int		s;
	char	**splitted;

	splitted = ft_strsplit(*cur, '/');
	s = (ft_array_length((void**)splitted) - 1);
	i = 0;
	if (s <= 0)
		ft_strcpy(*cur, "/");
	else
	{
		if (*cur[0] == '/')
		{
			ft_strcpy(*cur, "/");
			ft_strcat(*cur, splitted[0]);
		}
		else if (splitted)
			ft_strcpy(*cur, splitted[0]);
		while (splitted && splitted[++i] && i < s)
		{
			ft_strcat(*cur, "/");
			ft_strcat(*cur, splitted[i]);
		}
	}
	delete_array(splitted);
}

char		*set_sym_path(int i, char **sym, char **splitted)
{
	if (ft_strequ(splitted[i], ".."))
		prev_path(sym);
	else if (!ft_strequ(splitted[i], "."))
	{
		if (((int)ft_strlen(*sym) - 1) > 1 &&
			(*sym)[((int)ft_strlen(*sym) - 1)] != '/')
			ft_strcat((*sym), "/");
		ft_strcat((*sym), splitted[i]);
	}
	return (*sym);
}

char		*get_sym_path(char *cur, char *path)
{
	int		i;
	char	*sym;
	char	**splitted;

	sym = ft_memalloc(4096);
	splitted = ft_strsplit(path, '/');
	if (!cur || !path)
	{
		delete_array(splitted);
		return (NULL);
	}
	if (path[0] != '/')
	{
		sym[0] = 0;
		ft_strcpy(sym, cur);
	}
	else
		ft_strcpy(sym, "/");
	i = -1;
	while (splitted && splitted[++i])
		sym = set_sym_path(i, &sym, splitted);
	if (((int)ft_strlen(sym) - 1) >= 0 && sym[((int)ft_strlen(sym) - 1)] != '/')
		ft_strcat(sym, "/");
	delete_array(splitted);
	return (sym);
}

int			get_path(char *cmd, char **path, char ***env)
{
	if (cmd == NULL)
	{
		if (!(*path = ft_getenv_choice("HOME", *env)))
			return (cd_error("HOME is not set", 3));
	}
	else if (ft_strequ("-", cmd))
	{
		if (!(*path = ft_getenv_choice("OLDPWD", *env)))
			return (cd_error("OLDPWD is not set", 3));
	}
	else
		*path = cmd;
	return (1);
}
