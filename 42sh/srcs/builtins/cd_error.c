/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 18:55:30 by smondesi          #+#    #+#             */
/*   Updated: 2019/07/02 21:17:54 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int			usage_error(char c)
{
	ft_putstr_fd("42sh: cd: -", 2);
	ft_putchar_fd(c, 2);
	ft_putendl_fd(": invalid option", 2);
	ft_putendl_fd("cd: usage: cd [-L|-P] [dir]", 2);
	return (-1);
}

int			cd_error(char *cmd, int i)
{
	ft_putstr_fd("cd: ", 2);
	if (i == 0)
		ft_putstr_fd("not a directory: ", 2);
	if (i == 1)
		ft_putstr_fd("no such file or directory: ", 2);
	if (i == 2)
		ft_putstr_fd("Permission denied: ", 2);
	ft_putendl_fd(cmd, 2);
	return (1);
}

void		call_set_env(char ***env)
{
	char **set;

	if (*env == NULL)
		return ;
	set = create_key_value_env("OLDPWD", g_shell->pwd->oldpwd);
	builtin_setenv(set, env);
	delete_array(set);
	set = create_key_value_env("PWD", g_shell->pwd->pwd);
	builtin_setenv(set, env);
	delete_array(set);
}
