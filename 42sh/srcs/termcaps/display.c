/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 16:33:31 by rlucas-d          #+#    #+#             */
/*   Updated: 2019/10/26 16:33:32 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		display_name(void)
{
	char	*dir;
	int		len_dir;

	if (!(dir = get_dirpath()))
		exit_shell_code("malloc error", MALLOC_FAILURE);
	len_dir = ft_strlen(dir);
	ft_putstr("\033[93m");
	ft_putstr(dir);
	ft_putstr(" > ");
	ft_putstr("\033[0m");
	ft_strdel(&dir);
	return (len_dir + 3);
}

int		display_name_len(void)
{
	if (g_shell->pwd->pwd[ft_strlen(g_shell->pwd->pwd) - 1] == '/')
		g_shell->pwd->pwd[ft_strlen(g_shell->pwd->pwd) - 1] = '\0';
	return (ft_strlen(g_shell->pwd->pwd) + 3);
}

int		only_arrow(void)
{
	ft_putstr("\033[93m");
	ft_putstr(" > ");
	ft_putstr("\033[0m");
	return (3);
}

int		ft_reasearch_prompt(void)
{
	ft_putstr("\033[93m");
	ft_putstr("reasearch_MTF ");
	ft_putstr("\033[0m");
	return (14);
}

void	choose_display(t_termcaps *termcaps)
{
	if (termcaps->display_option == 1)
		termcaps->path = display_name();
	else if (termcaps->display_option == 2)
		termcaps->path = only_arrow();
	else
		termcaps->path = ft_reasearch_prompt();
}
