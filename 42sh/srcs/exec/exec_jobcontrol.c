/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_jobcontrol.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 21:28:34 by vjovanov          #+#    #+#             */
/*   Updated: 2019/09/20 12:06:26 by rlucas-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <sys/types.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

/*
** C'est ici qu'on va definir la fonction qui est appele si lors de la lecture
** de l'arbre, on tombe sur un token 'JOBCONTROL_TOKEN'
**
** Cette fonction doit retourner egalement 0 ou 1 en fonction de sa reussite
**
** Fonctionnement: (je pense)
** on va juste faire un fork particulier qui va permettre de dissocier d'une
**	certaine maniere l'enfant du parent sans le perdre pour autant.
**	Dans ce fork on va simplement faire un exec_left ou exec_right (ca depend
**	simplement de comment c'est dans l'arbre, donc a check).
**	Et comme chaque execution de token gere sa partie, ce qui doit etre lance
**	en background sera lance dans l'enfant pendant que le reste de l'arbre
**	est execute dans le parent (donc le shell principal)
**pid_t shell_pgid;
** struct termios shell_tmodes;
** int shell_terminal;
**int shell_is_interactive;
*/

/*
**void		init_job(void)
**{
**	shell_terminal = STDIN_FILENO;
**	shell_is_interactive = isatty (shell_terminal);
**
**	if (shell_is_interactive)
**	{
**		// Loop until we are in the foreground.
**		printf("%d\n", tcgetpgrp (shell_terminal));
**		printf("%d\n", getpgrp ());
**		while
**			(tcgetpgrp (shell_terminal) != (shell_pgid = getpgrp ()))
**				kill (- shell_pgid, SIGTTIN);
**		//printf("%d\n", tcgetpgrp (shell_terminal));
**		// Ignore interactive and job-control signals.
**		signal (SIGINT, SIG_IGN);
**		signal (SIGQUIT, SIG_IGN);
**		signal (SIGTSTP, SIG_IGN);
**		signal (SIGTTIN, SIG_IGN);
**		signal (SIGTTOU, SIG_IGN);
**		signal (SIGCHLD, SIG_IGN);
**
**		// Put ourselves in our own process group.
**		shell_pgid = getpid ();
**
**		if (setpgid (shell_pgid, shell_pgid) < 0)
**		{
**			perror ("Couldn't put the shell in its own process group");
**			exit (1);
**		}
**		// Grab control of the terminal.
**		tcsetpgrp (shell_terminal, shell_pgid);
**	Save default terminal attributes for shell.
**		tcgetattr (shell_terminal, &shell_tmodes);
**	}
**	return;
**}
*/

void	job(int nb)
{
    nb = 0;
	g_shell->exit_status = 1;
	g_shell->stop = 1;
	g_shell->termcaps->display_option = 1;
    ft_printf("\n");
	ft_printf("[STOPED]\n");
	g_shell->stdin_copy = dup(0);
	close(0);
	choose_display(g_shell->termcaps);
	return ;
}
