/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 19:39:07 by bjovanov          #+#    #+#             */
/*   Updated: 2019/07/02 22:50:16 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int			iflag(char **cmd)
{
	int i;
	int j;

	i = 0;
	while (cmd[i])
	{
		j = 1;
		if (cmd[i][0] != '-' || (cmd[i][0] == '-' && cmd[i][1] &&
			cmd[i][1] == '-'))
			return (i);
		while (cmd[i][j])
		{
			if (cmd[i][j] != 'i')
				return (error_option(cmd[i][j]));
			j++;
		}
		i++;
	}
	return (i);
}

int			verify_argument(char *cmd)
{
	char			*full_path;
	struct stat		file;

	if (cmd == NULL)
		return (1);
	full_path = find_path(cmd);
	if (lstat(full_path, &file) != 0)
		return (print_error_path(cmd, 0, full_path));
	if (access(full_path, R_OK) != 0)
		return (print_error_path(cmd, 1, full_path));
	ft_strdel(&full_path);
	return (1);
}

int			execute_env(char ***env, char **cmd, int i, char *cmd_position)
{
	pid_t	child;
	char	*path;
	int		status;

	path = NULL;
	status = 0;
	if (!(verify_argument(cmd_position)))
		return (free_darray(*env, 1));
	if (cmd_position == NULL)
		return (delete_array_print(*env));
	if ((child = fork()) == 0)
	{
		if ((path = find_path(cmd_position)) != NULL)
			if ((execve(path, &(cmd[find_index(cmd, i)]), *env)) == -1)
				exit_shell_code("execve error", 1);
		ft_strdel(&path);
		exit(EXIT_SUCCESS);
	}
	else if (child == -1)
		exit_shell_code("fork error", 1);
	waitpid(child, &status, 0);
	delete_array(*env);
	return (WEXITSTATUS(status));
}

void		check_option(int i, char ***new_env, char **env)
{
	if (i != 0)
		*new_env = strdup_array(env, 0);
	else
		*new_env = strdup_array(env, 1);
}

int			builtin_env(char ***env, char **cmd)
{
	int		j;
	int		i;
	int		end;
	char	**new_env;

	if (cmd[0] == NULL)
		return (print_env(*env));
	i = iflag(cmd);
	if (i == -1)
		return (1);
	new_env = NULL;
	check_option(i, &new_env, *env);
	j = i - 1;
	while (cmd[++j])
	{
		end = 0;
		if (is_variable_env(cmd[j], '='))
			setenv_tmp_env(cmd[j], &new_env, &end);
		if (end == 0)
			break ;
	}
	return (execute_env(&new_env, cmd, i, cmd[j]));
}
