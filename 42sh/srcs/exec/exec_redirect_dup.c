/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect_dup.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 20:00:54 by bjovanov          #+#    #+#             */
/*   Updated: 2019/07/06 19:07:31 by bjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		dup_to_both(int *file, t_redirect *tmp)
{
	if (tmp->std == -2)
	{
		dup2(*file, STDOUT_FILENO);
		dup2(*file, STDERR_FILENO);
		close(*file);
	}
}

void		dup_to_stdin(int *file, t_redirect *tmp)
{
	if (tmp->std == 0)
	{
		if (tmp->name == GREAT_TOKEN || tmp->name == DGREAT_TOKEN)
		{
			dup2(*file, STDIN_FILENO);
			close(*file);
		}
		else if (tmp->name == GREATAND_TOKEN)
		{
			if (is_valid_fd(tmp->path))
			{
				if (is_dash(tmp->path))
				{
					*file = open("/dev/null", O_WRONLY, 0644);
					dup2(*file, STDIN_FILENO);
					close(*file);
				}
				else
					dup2(ft_atoi(tmp->path), STDIN_FILENO);
			}
		}
	}
}

void		dup_to_stdout(int *file, t_redirect *tmp)
{
	if (tmp->std == 1)
	{
		if (tmp->name == GREAT_TOKEN || tmp->name == DGREAT_TOKEN)
		{
			dup2(*file, STDOUT_FILENO);
			close(*file);
		}
		else if (tmp->name == GREATAND_TOKEN)
		{
			if (is_valid_fd(tmp->path))
			{
				if (is_dash(tmp->path))
				{
					*file = open("/dev/null", O_WRONLY, 0644);
					dup2(*file, STDOUT_FILENO);
					close(*file);
				}
				else
					dup2(ft_atoi(tmp->path), STDOUT_FILENO);
			}
		}
	}
}

void		dup_to_stderr(int *file, t_redirect *tmp)
{
	if (tmp->std == 2)
	{
		if (tmp->name == GREAT_TOKEN || tmp->name == DGREAT_TOKEN)
		{
			dup2(*file, STDERR_FILENO);
			close(*file);
		}
		else if (tmp->name == GREATAND_TOKEN)
		{
			if (is_valid_fd(tmp->path))
			{
				if (is_dash(tmp->path))
				{
					*file = open("/dev/null", O_WRONLY, 0644);
					dup2(*file, STDERR_FILENO);
					close(*file);
				}
				else
					dup2(ft_atoi(tmp->path), STDERR_FILENO);
			}
		}
	}
}

void		dup_files(t_redirect *files, int *file)
{
	t_redirect *tmp;

	tmp = files;
	while (tmp)
	{
		create_files(tmp, file);
		dup_to_both(file, tmp);
		dup_to_stdin(file, tmp);
		dup_to_stdout(file, tmp);
		dup_to_stderr(file, tmp);
		tmp = tmp->next;
	}
}
