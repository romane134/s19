/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 19:38:25 by bjovanov          #+#    #+#             */
/*   Updated: 2019/07/02 22:33:16 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int			get_option(char **cmd, char *option)
{
	int i;
	int j;

	i = 0;
	if (cmd == NULL)
		return (0);
	while (cmd[i])
	{
		if (cmd[i][0] != '-' || ft_strequ("-", cmd[i]))
			return (i);
		if (ft_strequ(cmd[i], "--"))
			return (i + 1);
		j = 0;
		while (cmd[i][++j])
		{
			if (cmd[i][j] != 'L' && cmd[i][j] != 'P')
				return (usage_error(cmd[i][j]));
			*option = cmd[i][j];
		}
		i++;
	}
	return (i);
}

char		**create_key_value_env(char *item, char *path)
{
	char **set_env;

	if (!(set_env = (char**)malloc(sizeof(char*) * 3)))
		exit_shell_code("malloc error", MALLOC_FAILURE);
	if (!(set_env[0] = ft_strdup(item)))
		exit_shell_code("malloc error", MALLOC_FAILURE);
	if (!(set_env[1] = ft_strdup(path)))
		exit_shell_code("malloc error", MALLOC_FAILURE);
	set_env[2] = NULL;
	return (set_env);
}

int			cd_p_option(char *cmd, char ***env)
{
	struct stat	file;
	char		*path;

	path = NULL;
	if (!get_path(cmd, &path, env))
		return (1);
	if (stat(path, &file) != 0)
		return (cd_error(path, 1));
	if (!S_ISDIR(file.st_mode))
		return (cd_error(path, 0));
	if (access(path, R_OK) != 0)
		return (cd_error(path, 2));
	return (construct_full_path(path, env));
}

int			cd_no_option(char *cmd, char ***env)
{
	struct stat	file;
	char		*path;
	char		*sympath;

	path = NULL;
	if (!get_path(cmd, &path, env))
		return (1);
	if (stat(path, &file) != 0)
		return (cd_error(path, 1));
	if (!S_ISDIR(file.st_mode))
		return (cd_error(path, 0));
	if (access(path, R_OK) != 0)
		return (cd_error(path, 2));
	sympath = get_sym_path(g_shell->pwd->pwd, path);
	ft_strdel(&(g_shell->pwd->oldpwd));
	chdir(sympath);
	g_shell->pwd->oldpwd = g_shell->pwd->pwd;
	g_shell->pwd->pwd = sympath;
	call_set_env(env);
	return (0);
}

int			builtin_cd(char ***env, char **cmd)
{
	char	option;
	int		i;

	option = '\0';
	if ((i = get_option(cmd, &option)) == -1)
		return (1);
	if (option == 'P')
		return (cd_p_option(cmd[i], env));
	else
		return (cd_no_option(cmd[i], env));
}
