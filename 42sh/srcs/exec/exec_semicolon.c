/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_semicolon.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjovanov <vjovanov@student.19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 21:28:19 by vjovanov          #+#    #+#             */
/*   Updated: 2019/07/06 17:42:18 by vjovanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
** Gestion du token ';'
*/

int	exec_semicolon(t_token *ast, char ***env)
{
	if (has_bad_substitution(ast->left->value))
		return (1);
	if (exec(ast->left, env) == BAD_SUB_CODE)
		return (1);
	if (ast->right)
	{
		if (has_bad_substitution(ast->right->value))
			return (1);
		if (exec(ast->right, env) == BAD_SUB_CODE)
			return (1);
	}
	return (0);
}
