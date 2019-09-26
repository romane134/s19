/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 11:13:01 by bjovanov          #+#    #+#             */
/*   Updated: 2019/07/02 22:34:05 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		is_valid_pwd(char *pwd)
{
	struct stat file;

	if (lstat(pwd, &file) != 0)
		return (0);
	if (!S_ISLNK(file.st_mode))
		return (0);
	if (stat(pwd, &file) != 0)
		return (0);
	if (!S_ISDIR(file.st_mode))
		return (0);
	if (access(pwd, R_OK) != 0)
		return (0);
	return (1);
}

char	*get_pwd(void)
{
	char	buf[4097];
	char	*pwd;

	pwd = NULL;
	if (!(pwd = ft_getenv("PWD")))
	{
		if (!is_valid_pwd(pwd))
		{
			ft_memset(buf, '\0', 4097);
			if (!(getcwd(buf, 4096)))
				exit_shell("getcwd error");
			if (!(pwd = ft_strdup(buf)))
				exit_shell_code("malloc error", MALLOC_FAILURE);
		}
	}
	else
	{
		if (!(pwd = ft_strdup(pwd)))
			exit_shell_code("malloc error", MALLOC_FAILURE);
	}
	return (pwd);
}

void	set_pwd(void)
{
	char		*pwd;


	if (!(pwd = get_pwd()))
		exit_shell("get_pwd error");
	if (!(g_shell->pwd = malloc(sizeof(*g_shell->pwd))))
		exit_shell_code("malloc error", MALLOC_FAILURE);
	g_shell->pwd->pwd = pwd;
	g_shell->pwd->oldpwd = NULL;
}
