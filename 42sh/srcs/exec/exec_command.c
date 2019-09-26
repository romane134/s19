/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 21:28:45 by vjovanov          #+#    #+#             */
/*   Updated: 2019/07/27 19:07:58 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
** t_token *ast = arbre syntaxique mis au token command correspond
** char **cmd = la commande splitte comme il faut
** ex: ls -la ==> ls | -la
** int i = l'index de depart dans la commande
** ex: prevu dans le cas d'un "a=b | c=a | ls | -la", le i = 2
** 0     1     2    3
** char ***env = l'environnement (soit g_shell->env ou l'env temporaire
** si par ex : "HOME=/ tmp")
** Le retour de la commande est vraiment important, c'est lui qui permet
** de savoir grace a la commande "echo $?" si la commande a fonctionne ou pas
** 0 = reussi | > 0 = fail
** WARNING: SI TU RAJOUTES UN BUILTIN, IL FAUT EGALEMENT RAJOUTER CE BUILTIN
** DANS LA FONCTION 'is_builtin' QUI SE TROUVE DANS LE FICHIER :
** exec_command_utils.c
*/

int			try_builtin_expand(t_token *ast, char **cmd, int i, char ***env)
{
	if (ft_strequ(cmd[i], "hash"))
		hash_builtin();
	else if (ft_strequ(cmd[i], "fc"))
		builtin_fc(&(cmd[i + 1]));
	else if (ft_strequ(cmd[i], "exit"))
		builtin_exit(&(cmd[i + 1]), ast);
	return (0 && env);
}

int			try_builtin(t_token *ast, char **cmd, int i, char ***env)
{
	int ret;

	ret = -2;
	if (ft_strequ(cmd[i], "cd"))
		ret = builtin_cd(env, &(cmd[i + 1]));
	else if (ft_strequ(cmd[i], "echo"))
		ret = builtin_echo(&(cmd[i + 1]));
	else if (ft_strequ(cmd[i], "env"))
		ret = builtin_env(env, &(cmd[i + 1]));
	else if (ft_strequ(cmd[i], "setenv"))
		ret = builtin_setenv(&(cmd[i + 1]), env);
	else if (ft_strequ(cmd[i], "unsetenv"))
		ret = builtin_unsetenv(&(cmd[i + 1]), env);
	else
		ret = try_builtin_expand(ast, cmd, i, env);
	free_darray(cmd, 1);
	if (*env != g_shell->env)
		free_darray(*env, 1);
	if (ret != -2)
		g_shell->exit_status = ret;
	if (g_shell->i == 1)
		g_shell->exit_status = 130;
	return (ret == -2 ? -1 : ret);
}

/*
** Checke la validite de la commande pour etre sur qu'elle peut etre
** execute sans probleme ou bien retourner le bon code erreu
*/

int			check_validity(char *path_cmd, char *cmd)
{
	struct stat	info;

	if (stat(path_cmd, &info) != -1)
	{
		if (info.st_mode & S_IFDIR)
		{
			return (print_error_return(cmd, "is a directory", 126));
		}
		if (info.st_mode & S_IXUSR && info.st_mode & S_IFREG)
			return (0);
		else
			return (print_error_return(cmd, "permission denied", 126));
	}
	else
	{
		if (!ft_strchr(path_cmd, '/'))
			return (print_error_return(cmd, "command not found", 127));
		else
			return (print_error_return(cmd, "no such file or directory", 127));
	}
	return (1);
}

/*
** 1) Il appelle la fonction expansion_handle pour gerer ~ , $ et ${}
** 2) Il parse la commande, donc juste il splitte aux bons endroits en
**    prenant compte des "", '' et \
** 3) Si un dollar est toujours restant dans la commande parse, ca veut dire
**    qu'il y a eu un bad substitution (ex: ${HOME }) et du coup stop le prog
** 4) Il appelle la fonction clear_cmd qui s'occupe de retirer tous les
**		quotes, dquote et backslash qui doivent etre enleves
** 5) Si des variables d'environnements sont modifies avant d'exec la command
**		ex: HOME=/ cd
**	  dans ce cas, on definit un environnement temporaire qui servira durant
**	  tout la duree de la commande
**	    ex: HOME=/ cd ; ls \\\ l'environnement temporaire servira que pour cd
*/

int			exec_command(t_token *ast, char ***env)
{
	char	**cmd;
	int		j_for_bad;
	char	**tmp_env;
	int		i;

	j_for_bad = -1;
	i = 0;
	tmp_env = NULL;
	expansions_handle(&(ast->value), *env);
	if (ft_strcmp(ast->value, "") == 0)
		return (0);
	cmd = parse_cmd(ast->value);
	if (is_bad_substitution(cmd, j_for_bad, j_for_bad))
	{
		g_shell->exit_status = 1;
		return (free_darray(cmd, BAD_SUB_CODE));
	}
	clear_cmd(cmd);
	while (cmd[i] && ft_strchr(cmd[i], '='))
		i++;
	if (i > 0 && cmd[i] == NULL)
		set_intern_var(cmd);
	else if (i > 0 && cmd[i] != NULL)
		set_temp_env(cmd, &tmp_env, env);
	return (exec_core(ast, cmd, (tmp_env == NULL) ? env : &tmp_env, i));
}
