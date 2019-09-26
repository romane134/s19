/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 21:29:17 by vjovanov          #+#    #+#             */
/*   Updated: 2019/08/01 19:38:25 by bjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static char	**split_redirect(char *value, enum e_tokens name)
{
	char **arr;

	arr = NULL;
	if (name == DGREAT_TOKEN)
	{
		if (!(arr = ft_strstrsplit(value, ">>")))
			exit_shell_code("malloc error", MALLOC_FAILURE);
	}
	else if (name == GREAT_TOKEN || name == ANDGREAT_TOKEN)
	{
		if (!(arr = ft_strstrsplit(value, ">")))
			exit_shell_code("malloc error", MALLOC_FAILURE);
	}
	else if (name == GREATAND_TOKEN)
	{
		if (!(arr = ft_strstrsplit(value, ">&")))
			exit_shell_code("malloc error", MALLOC_FAILURE);
	}
	return (arr);
}

static int	exec_one_redirect(t_token *tmp, t_redirect **files, int position)
{
	char **arr;

	arr = NULL;
	if (!is_right_redirect(tmp->name))
	{
		if (!(exec_left_redirect(tmp, position)))
			return (0);
	}
	else
	{
		arr = split_redirect(tmp->value, tmp->name);
		if (position == 1)
		{
			if (has_bad_substitution(tmp->right->left->value))
				exit(BAD_SUB_CODE);
			add_redirect_item(files, tmp->right->left->value, tmp->name,
				check_fd(arr[0]));
		}
		else
			add_redirect_item(files, tmp->right->value, tmp->name,
				check_fd(arr[0]));
		delete_array(arr);
	}
	return (1);
}

static int	add_files(t_token *ast, t_redirect **files)
{
	t_token *tmp;

	tmp = ast;
	if (ast->right->name == COMMAND_TOKEN)
	{
		if (has_bad_substitution(ast->right->value))
			exit(BAD_SUB_CODE);
		expansions_handle(&(ast->right->value), g_shell->env);
		return (exec_one_redirect(tmp, files, 0));
	}
	while (tmp->right && tmp->right->left)
	{
		expansions_handle(&(tmp->right->left->value), g_shell->env);
		if (!(exec_one_redirect(tmp, files, 1)))
			return (0);
		tmp = tmp->right;
	}
	if (tmp->right)
	{
		if (has_bad_substitution(tmp->right->value))
			exit(BAD_SUB_CODE);
		expansions_handle(&(tmp->right->value), g_shell->env);
		return (exec_one_redirect(tmp, files, 2));
	}
	return (1);
}

void		create_files(t_redirect *tmp, int *file)
{
	if (tmp->name == GREAT_TOKEN || tmp->name == ANDGREAT_TOKEN)
		*file = open(tmp->path, O_TRUNC | O_CREAT | O_WRONLY, 0644);
	else if (tmp->name == DGREAT_TOKEN)
		*file = open(tmp->path, O_APPEND | O_CREAT | O_WRONLY, 0644);
}

int			exec_redirect(t_token *ast, char ***env)
{
	pid_t		child;
	t_redirect	*files;
	int			file;
	int			status;

	file = -1;
	files = NULL;
	if ((child = fork()) == 0)
	{
		if (ast->left && has_bad_substitution(ast->left->value))
			exit(BAD_SUB_CODE);
		if (!(add_files(ast, &files)))
			exit(delete_redirect(&files, 1));
		dup_files(files, &file);
		close(file);
		delete_redirect(&files, 1);
		status = exec(ast->left, env);
		exit(status);
	}
	else if (child == -1)
		exit_shell_code("fork error", 1);
	waitpid(child, &status, 0);
	g_shell->exit_status =
		(WEXITSTATUS(status) == BAD_SUB_CODE) ? 1 : WEXITSTATUS(status);
	return ((WEXITSTATUS(status) == BAD_SUB_CODE) ? BAD_SUB_CODE : status);
}
