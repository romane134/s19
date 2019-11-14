/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjovanov <bjovanov@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 09:04:13 by bjovanov          #+#    #+#             */
/*   Updated: 2019/09/17 14:43:48 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		start_process(char *line)
{
	t_token		*token_list;

	token_list = NULL;
	if (line == NULL || is_only_space(line))
	{
		ft_strdel(&line);
		return ;
	}
	signal(SIGINT, stop);
	close_command(&line, g_shell->termcaps);
	if ((token_list = lexer(&line)) && check_token_list(&token_list, &line,
		g_shell->termcaps))
	{
		add_in_history(g_shell->termcaps, line);
		handle_left_redirect(token_list, g_shell->termcaps);
		if (g_shell->stop == 1)
		{
			g_shell->stop = 0;
			delete_token_list(&token_list);
			ft_strdel(&line);
			return ;
		}
		signal(SIGINT, sig);
		token_list = parseur(token_list);
		exec(token_list, &(g_shell->env));
	}
	if (g_shell->stop == 1)
		g_shell->stop = 0;
	delete_token_list(&token_list);
	ft_strdel(&line);
}

int			main(int argc, char **argv, char **env)
{
	char		*line;
	t_termcaps	termcaps;

	if (tcgetattr(0, &termcaps.term_restore) == -1)
		exit(-1);
	bootstrap(env);
	term_init(&termcaps);
	g_shell->termcaps = &termcaps;
	line = NULL;
	while (1)
	{
		ft_printf("\n");
		g_shell->sig = 1;
		g_shell->i = 0;
		g_shell->stop = 0;
		signal(SIGINT, sig);
		signal(SIGTSTP, SIG_IGN);
		line = termcaps_main(&termcaps, 1);
		start_process(line);
	}
	return (argc && argv && env && 0);
}
