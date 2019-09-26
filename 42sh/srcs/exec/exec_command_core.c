/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command_core.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 10:39:59 by vjovanov          #+#    #+#             */
/*   Updated: 2019/07/17 12:46:00 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
** C'est ici qu'on execute la commande.
** On fait appel a la fonction check_validity qui se trouve dans exec_command.c
** pour verifier que la commande peut correctement etre execute.
**
** Si check validity fail, on n'execute pas et on retourne le code d'erreur
** que check validity nous a retourne et la fonction check_validity s'occupe
** d'ecrire le bon message d'erreur a l'ecran
*/

static void	exec_child(char **cmd, int i, char ***env, char **path)
{
	int		ret;

	if (!(ret = check_validity(*path, cmd[i])))
		if ((execve(*path, &(cmd[i]), *env)) == -1)
			exit_shell_code("execve error", 1);
	ft_strdel(path);
	exit(ret);
}

/*
** Cette fonction fait un premier test sur la commande.
** Si la fonction ne possede aucun '/', on a du coup d'office une fonction
** du genre: 'ls', 'chmod', ...
**
** On va donc verifier dans la hash table si on trouve cette commande.
** Si on ne trouve pas la commande dans la hash table, cela veut dire que
** c'est obligatoirement une mauvaise commande du genre: "unknow", 'ola', ...
**
** Par contre, si la commande contient un '/', alors, on ne fait simplement
** que continuer et on fera des tests plus precis grace a la fonction
** 'check_validity' qui se trouve dans exec_command.c juste avant d'executer
** la commande
*/

char		*find__path(char **cmd, int i)
{
	char	*path;

	if (!ft_strchr(cmd[i], '/'))
	{
		if (!(path = find_hash(g_hash_table, cmd[i], HASHTABLE_SIZE)))
		{
			print_error(cmd[i], "command not found");
			return (NULL);
		}
		else
			path = ft_strdup(path);
	}
	else if (cmd[i][0] == '/')
		path = ft_strdup(cmd[i]);
	else
		path = ft_str3join(getcwd(NULL, 0), "/", cmd[i]);
	if (path == NULL)
		exit_shell_code("malloc error", MALLOC_FAILURE);
	return (path);
}

/*
** Ici, c'est la fonction qui fait l'execution de la commande apres
** qu'elle ait ete parse, clear, et qu'on lui ai bien modifie toutes
** ses expansions avec les valeurs prevue
**
** Il va d'abord appeler la fonction set_underscore_var qui se trouve
** dans expansions/dollar.c pour set la variable d'environnement '$_'
** Ensuite il commence par verifier si la commande qu'il doit executer est
** un builtin.
** Si oui, simplement, le built-in s'execute et ensuite, la fonction s'arrete
** la et retourne le code retourne par le builtin.
**
** Si non, si ca n'est pas un builtin, ca veut dire que c'est une commande,
** (logique lol).
** Il va du coup, pour ça, commencer par aller verifier une premiere chose:
**		- la commande se trouve-t-elle dans la table de hash generale ?
** Pour ca, il va appeler la fonction find__path. Le fonctionnement de la
** fonction est explique au dessus de la fonction en question.
**
** Si la fonction a dit que ce n'etait pas une commande valide, dans ce cas
** on arrete l'execution et on retourne le code d'erreur 127.
**
** Sinon, on continue. On fork pour lancer l'execution dans un enfant.
*/

int			exec_core(t_token *ast, char **cmd, char ***env, int i)
{
	int		status;
	pid_t	ok;
	char	*path;

	status = 0;
	signal (SIGTSTP, job);
	if (set_underscore_var(cmd, env) && cmd[i])
	{
		if (is_builtin(cmd[i]))
			return (try_builtin(ast, cmd, i, env));
		if (!(path = find__path(cmd, i)))
		{
			free_darray(cmd, 1);
			return (g_shell->exit_status = 127);
		}
		if ((ok = fork()) == 0)
			exec_child(cmd, i, env, &path);
		else if (ok == -1)
			exit_shell_code("fork error", 1);
		ft_strdel(&path);
		waitpid(ok, &status, 0);
		g_shell->exit_status = WEXITSTATUS(status);
		if (g_shell->i == 1)
			g_shell->exit_status = 130;
	}
	return (free_darray(cmd, g_shell->exit_status));
}
