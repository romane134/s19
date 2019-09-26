/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_left_redirect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 13:30:26 by bcedric           #+#    #+#             */
/*   Updated: 2019/07/06 19:43:53 by bjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static int		return_error(char *error, char *value, char **arr)
{
	ft_putstr_fd("42sh: ", 2);
	ft_putstr_fd(error, 2);
	ft_putendl_fd(value, 2);
	delete_array(arr);
	return (0);
}

static char		**split_redirect(char *value, enum e_tokens name)
{
	char **arr;

	arr = NULL;
	if (name == DLESS_TOKEN)
	{
		if (!(arr = ft_strstrsplit(value, "<<")))
			exit_shell_code("malloc error", MALLOC_FAILURE);
	}
	else if (name == LESS_TOKEN)
	{
		if (!(arr = ft_strstrsplit(value, "<")))
			exit_shell_code("malloc error", MALLOC_FAILURE);
	}
	else if (name == LESSAND_TOKEN)
	{
		if (!(arr = ft_strstrsplit(value, "<&")))
			exit_shell_code("malloc error", MALLOC_FAILURE);
	}
	return (arr);
}

static int		exec_dless_token(t_token *ast, char *value)
{
	pid_t	child;
	int		fd[2];
	char	**arr;
	int		status;

	if ((status = 0) == 0 && pipe(fd) == -1)
		exit_shell_code("pipe error", 1);
	if ((child = fork()) == 0)
		exec_child_dless_token(fd, value);
	else if (child == -1)
		exit_shell_code("fork error", 1);
	waitpid(child, &status, 0);
	g_shell->exit_status = WEXITSTATUS(status);
	close(fd[1]);
	arr = split_redirect(ast->value, ast->name);
	if (dup2(fd[0], arr[0] ? ft_atoi(arr[0]) : STDIN_FILENO) == -1)
	{
		close(fd[0]);
		return (return_error("bad file descriptor: ", value, arr));
	}
	delete_array(arr);
	return (!close(fd[0]));
}

static int		exec_less_token(t_token *ast, char *value)
{
	int			file;
	struct stat infos;
	char		**arr;

	arr = split_redirect(ast->value, ast->name);
	if (ast->name == LESS_TOKEN)
	{
		if (lstat(value, &infos) == -1)
			return (return_error("No such file or directory: ", value, arr));
		if (access(value, R_OK) != 0)
			return (return_error("Permission denied: ", value, arr));
		file = open(value, O_RDONLY, 0644);
		dup2(file, arr[0] ? ft_atoi(arr[0]) : STDIN_FILENO);
		close(file);
	}
	else if (ast->name == LESSAND_TOKEN)
		if (dup2(ft_atoi(value), arr[0] ? ft_atoi(arr[0]) : STDIN_FILENO) == -1)
			return (return_error("bad file descriptor: ", value, arr));
	delete_array(arr);
	return (1);
}

int				exec_left_redirect(t_token *ast, int position)
{
	char *value;

	if (position == 0 || position == 2)
		value = ast->right->value;
	else
		value = ast->right->left->value;
	if (ast->name == LESS_TOKEN || ast->name == LESSAND_TOKEN)
	{
		if (!(exec_less_token(ast, value)))
			return (0);
	}
	else
	{
		if (!(exec_dless_token(ast, value)))
			return (0);
	}
	return (1);
}
