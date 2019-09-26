/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcedric <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 15:17:17 by bcedric           #+#    #+#             */
/*   Updated: 2019/06/22 15:17:18 by bcedric          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		error_option(char option)
{
	ft_putstr_fd("env: illegal option -- ", 2);
	ft_putchar_fd(option, 2);
	ft_putchar_fd('\n', 2);
	ft_putendl_fd("usage: env [-i] [utility [argument ...]]", 2);
	return (-1);
}

int		error_setenv_tmp(char *c)
{
	ft_putstr_fd("env: setenv ", 2);
	ft_putstr_fd(c, 2);
	ft_putendl_fd(": Invalid argument", 2);
	return (0);
}

int		print_error_path(char *cmd, int i, char *path)
{
	ft_strdel(&path);
	if (i == 0)
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": No such file or directory", 2);
	}
	else
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": Permission denied", 2);
	}
	return (0);
}

int		delete_array_print(char **env)
{
	print_env(env);
	delete_array(env);
	return (0);
}
