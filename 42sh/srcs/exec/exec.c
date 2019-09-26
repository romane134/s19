/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 15:46:25 by vjovanov          #+#    #+#             */
/*   Updated: 2019/07/27 19:43:35 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
**
** Tout l'executable fonctionne en recursive
** Chaque token qui est necessaire a l'execution a son propre fichier
** Ici, c'est simplement un arbre de if qui s'occupe d'appeler la bonne
** fonction en fonction du token sur lequel il est
**
*/

int	exec(t_token *ast, char ***env)
{
	g_shell->sig = 0;
	if (ast->name == SEMICOLON_TOKEN)
		return (exec_semicolon(ast, env));
	else if (ast->name == JOBCONTROL_TOKEN)
	{
		//return (exec_jobcontrol(ast, env))
		exec(ast->left, env);
		exec(ast->right, env);
	}
	else if (ast->name == COMMAND_TOKEN)
		return (exec_command(ast, env));
	else if (is_redirect_token(ast->name))
		return (exec_redirect(ast, env));
	else if (ast->name == AND_IF_TOKEN)
		return (exec_andif(ast, env));
	else if (ast->name == OR_IF_TOKEN)
		return (exec_orif(ast, env));
	else if (ast->name == PIPE_TOKEN)
		return (exec_pipe(ast, env));
	return (1);
}
