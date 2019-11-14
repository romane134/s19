/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_c.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <smondesi@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 12:07:55 by rlucas-d          #+#    #+#             */
/*   Updated: 2019/08/01 22:37:33 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		ctrl_c(t_termcaps *termcaps, char **cmd)
{
	ft_strdel(cmd);
	*cmd = ft_strnew(0);
	termcaps->pos = 0;
	tputs(tgoto(termcaps->goup, 0, 0), 1, (void *)ft_putchar);
	termcaps->cmd_len = 0;
	g_shell->i = 0;
	ft_printf("\n");
}

char		*ctrl_c_heredoc(t_termcaps *termcaps, char **cmd)
{
	ft_strdel(cmd);
	*cmd = ft_strnew(0);
	termcaps->pos = 0;
	tputs(tgoto(termcaps->goup, 0, 0), 1, (void *)ft_putchar);
	tputs(tgoto(termcaps->goup, 0, 0), 1, (void *)ft_putchar);
	termcaps->cmd_len = 0;
	g_shell->stop = 1;
	ft_printf("\n");
	return (NULL);
}
