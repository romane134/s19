/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 21:29:07 by vjovanov          #+#    #+#             */
/*   Updated: 2019/07/06 17:44:04 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
** Execution de la commande de gauche dans un enfant
** Comme on peut voir, utilisation du has_bad_substitution pour etre sur
** qu'avant d'executer la commande, il n'y a pas de bad substitution dedans.
*/

void		exec_child(t_token *ast, int fd[2], char ***env)
{
	close(fd[0]);
	dup2(STDOUT_FILENO, STDERR_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	if (has_bad_substitution(ast->left->value))
		exit(BAD_SUB_CODE);
	exec(ast->left, env);
	close(fd[1]);
	exit(EXIT_SUCCESS);
}

/*
** Execution de la commande de droite du pipe dans le parent.
*/

void		exec_parent(t_token *ast, int fd[2], char ***env, pid_t child)
{
	int status;
	int new;
	int	ret;

	new = dup(STDIN_FILENO);
	dup2(fd[0], STDIN_FILENO);
	status = exec(ast->right, env);
	close(fd[0]);
	dup2(new, STDIN_FILENO);
	close(new);
	ret = 0;
	waitpid(child, &ret, 0);
	if (WEXITSTATUS(ret) == BAD_SUB_CODE ||
		WEXITSTATUS(status) == BAD_SUB_CODE)
		exit(BAD_SUB_CODE);
	exit(status);
}

/*
** S'occupe de gerer l'execution du token pipe
** Le pipe fonctionne dans un enfant.
**
** Le pipe execute les 2 parties le composant en meme temps et sa partie gauche
** est lance dans un enfant
** Ex: ls | grep e => ls et grep sont execute en meme temps et le ls est lance
**						dans un enfant
**
** On appelle dont l'execution du child (donc sa partie gauche)
** et des que l'appel a ete fait, on execute directement le grep.
**
** Le code d'erreur retourne par un pipe est le code d'erreur de la derniere
** commande. Ex: exit 1 | exit 2 | exit 3 => retourne 3
*/

int			exec_pipe(t_token *ast, char ***env)
{
	int		fd[2];
	pid_t	child;
	int		status;

	if ((child = fork()) == 0)
	{
		if (pipe(fd) == -1)
			exit_shell_code("pipe error", 1);
		if ((child = fork()) == 0)
			exec_child(ast, fd, env);
		else if (child == -1)
			exit_shell_code("fork error", 1);
		close(fd[1]);
		exec_parent(ast, fd, env, child);
	}
	else
		waitpid(child, &status, 0);
	g_shell->exit_status =
	(WEXITSTATUS(status) == BAD_SUB_CODE) ? 1 : WEXITSTATUS(status);
	return (WEXITSTATUS(status));
}
