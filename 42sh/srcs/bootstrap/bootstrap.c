/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bootstrap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 10:56:14 by bjovanov          #+#    #+#             */
/*   Updated: 2019/07/27 19:32:31 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

t_shell *g_shell;
t_hash **g_hash_table;

void	sig(int nb)
{
	nb = 0;
	g_shell->i = 1;
	g_shell->exit_status = 1;
	if (g_shell->sig == 1)
	{
		ft_printf("\n\n");
		choose_display(g_shell->termcaps);
	}
	return ;
}

void	stop(int nb)
{
	nb = 0;
	g_shell->exit_status = 1;
	g_shell->stop = 1;
	g_shell->termcaps->display_option = 1;
	ft_printf("\n\n");
	g_shell->stdin_copy = dup(0);
	close(0);
	choose_display(g_shell->termcaps);
}

void	bootstrap(char **env)
{
	if (!(g_shell = malloc(sizeof(*g_shell))))
		exit_shell_code("malloc error", MALLOC_FAILURE);
	g_shell->in = NULL;
	g_shell->handled_token = NULL;
	g_shell->exit_status = 0;
	set_environment(env);
	set_pwd();
	set_handled_token();
	set_hash(1);
	g_shell->intern_hash = make_hash(INTERN_HASH_SIZE);
	g_shell->alias_hash = make_hash(ALIAS_HASH_SIZE);
}
