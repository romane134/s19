/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 17:10:32 by bjovanov          #+#    #+#             */
/*   Updated: 2019/07/17 12:50:50 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void			delete_global(void)
{
	del_all_hash(g_hash_table, HASHTABLE_SIZE);
	ft_strdel(&(g_shell->pwd->pwd));
	if (g_shell->pwd->oldpwd)
		ft_strdel(&(g_shell->pwd->oldpwd));
}

static void		numeric_argument_error(char *cmd)
{
	ft_putstr_fd("42sh: exit: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": numeric argument required", 2);
}

void			builtin_exit(char **cmd, t_token *ast)
{
	int i;

	if (cmd == NULL || cmd[0] == NULL)
	{
		delete_global();
		exit(EXIT_SUCCESS);
	}
	if (ft_array_length((void**)cmd) >= 2)
	{
		ft_putendl_fd("42sh: exit: too many arguments", 2);
		g_shell->exit_status = 1;
		return ;
	}
	i = 0;
	while (cmd[0][i] && ft_isdigit(cmd[0][i]))
		i++;
	if (cmd[0][i] != '\0')
	{
		numeric_argument_error(cmd[0]);
		g_shell->exit_status = 1;
		return ;
	}
	delete_global();
	delete_token_list(&ast);
	exit(ft_atoi(cmd[0]));
}
